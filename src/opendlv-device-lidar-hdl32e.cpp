/*
 * opendlv-device-lidar-hdl32e decodes HDL32e data realized for OpenDLV.
 * Copyright (C) 2018  Christian Berger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "cluon-complete.hpp"
#include "opendlv-standard-message-set.hpp"
#include "hdl32e-decoder.hpp"

int32_t main(int32_t argc, char **argv) {
    int32_t retCode{0};
    auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);
    if ( (0 == commandlineArguments.count("hdl32e_port")) || (0 == commandlineArguments.count("cid")) ) {
        std::cerr << argv[0] << " decodes pointcloud data from a VelodyneLidar HDL32e unit and publishes it to a running OpenDaVINCI session using the OpenDLV Standard Message Set." << std::endl;
        std::cerr << "Usage:   " << argv[0] << " [--hdl32e_ip=<IPv4-address>] --hdl32e_port=<port> --cid=<OpenDaVINCI session> [--id=<Identifier in case of multiple lidars>] [--verbose]" << std::endl;
        std::cerr << "Example: " << argv[0] << " --hdl32e_ip=0.0.0.0 --hdl32e_port=2368 --cid=111" << std::endl;
        retCode = 1;
    } else {
        const uint32_t ID{(commandlineArguments["id"].size() != 0) ? static_cast<uint32_t>(std::stoi(commandlineArguments["id"])) : 0};
        const bool VERBOSE{commandlineArguments.count("verbose") != 0};

        // Interface to a running OpenDaVINCI session (ignoring any incoming Envelopes).
        cluon::OD4Session od4{static_cast<uint16_t>(std::stoi(commandlineArguments["cid"])),
            [](auto){}
        };

        // Interface to VelodyneLidar HDL32e unit.
        const std::string HDL32E_ADDRESS((commandlineArguments.count("hdl32e_ip") == 0) ? "0.0.0.0" : commandlineArguments["hdl32e_ip"]);
        const uint32_t HDL32E_PORT(std::stoi(commandlineArguments["hdl32e_port"]));
        HDL32eDecoder hdl32eDecoder;
        cluon::UDPReceiver fromDevice(HDL32E_ADDRESS, HDL32E_PORT,
            [&od4Session = od4, &decoder = hdl32eDecoder, senderStamp = ID, VERBOSE](std::string &&d, std::string &&/*from*/, std::chrono::system_clock::time_point &&tp) noexcept {
            auto retVal = decoder.decode(d);
            if (!retVal.empty()) {
                cluon::data::TimeStamp sampleTime = cluon::time::convert(tp);

                for(auto e : retVal) {
                    od4Session.send(e, sampleTime, senderStamp);
                }

                // Print values on console.
                if (VERBOSE) {
                    std::cout << "[lidar-hdl32e] Decoded data into PointCloudReading." << std::endl;
                }
            }
        });

        // Just sleep as this microservice is data driven.
        using namespace std::literals::chrono_literals;
        while (od4.isRunning()) {
            std::this_thread::sleep_for(1s);
        }
    }
    return retCode;
}
