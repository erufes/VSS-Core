/*
 * This file is part of the VSS-SDK project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _INTERFACE_CORE_H_
#define _INTERFACE_CORE_H_

#include <Interfaces/IStateReceiver.h>
#include "zmq.hpp"
#include "Communications/CommunicationBase.h"

namespace vss{

    class StateReceiver : public IStateReceiver, public CommunicationBase {
    public:
        StateReceiver();

        void createSocket() override;
        State receiveState(FieldTransformationType) override;
    };

}

#endif // _INTERFACE_CORE_H_
