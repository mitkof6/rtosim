/* -------------------------------------------------------------------------- *
 * Copyright (c) 2010-2016 C. Pizzolato, M. Reggiani                          *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License");            *
 * you may not use this file except in compliance with the License.           *
 * You may obtain a copy of the License at:                                   *
 * http://www.apache.org/licenses/LICENSE-2.0                                 *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 * -------------------------------------------------------------------------- */

#ifndef rtosim_MarkersFromTrc_h
#define rtosim_MarkersFromTrc_h

#include "rtb/concurrency/Latch.h"
#include "rtosim/queue/MarkerSetQueue.h"
#include <string>
#include <vector>
#include <OpenSim/OpenSim.h>

namespace rtosim{

    class MarkersFromTrc{

    public:
        MarkersFromTrc() = delete;
        MarkersFromTrc(MarkersFromTrc&) = delete;
        MarkersFromTrc(
            MarkerSetQueue& outputMarkerSetQueue,
            rtb::Concurrency::Latch& doneWithSubscriptions,
            rtb::Concurrency::Latch& doneWithExecution,
            const std::string& osimModelFilename,
            const std::string& trcFilename,
            bool loop = true);
        void setOutputFrequency(double frequency);
        void setSpeedFactor(double speedFactor);
        void setFramesToSkip(unsigned n);
        void operator()();
        virtual ~MarkersFromTrc();

    private:
        void sendEndOfData();
        std::chrono::milliseconds getSleepTime() const;
        unsigned framesToSkip_;
        double speedFactor_;
        unsigned sampleFrequency_;
        std::vector<MarkerSetFrame> frames_;
        MarkerSetQueue& outputMarkerSetQueue_;
        rtb::Concurrency::Latch& doneWithSubscriptions_;
        rtb::Concurrency::Latch& doneWithExecution_;
        std::string trcFilename_;
        OpenSim::Model model_;
        std::size_t noMarkers_;
        bool loop_;
    };
}

#endif
