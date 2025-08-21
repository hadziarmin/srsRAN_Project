#
# Copyright 2021-2025 Software Radio Systems Limited
#
# This file is part of srsRAN
#
# srsRAN is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of
# the License, or (at your option) any later version.
#
# srsRAN is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Affero General Public License for more details.
#
# A copy of the GNU Affero General Public License can be found in
# the LICENSE file in the top-level directory of this distribution
# and at http://www.gnu.org/licenses/.
#

find_package(PahoMqttCpp REQUIRED)

set(SOURCES
       mqtt.cpp)

add_library(srsran_mqtt_app_service STATIC ${SOURCES})
target_include_directories(srsran_mqtt_app_service PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(srsran_mqtt_app_service PRIVATE /usr/local/include)
target_link_libraries(srsran_mqtt_app_service PRIVATE /usr/local/lib/libpaho-mqttpp3.so /usr/local/lib/libpaho-mqtt3as.so)
