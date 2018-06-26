//
// Created by johnathan on 31/05/18.
//

#include <Communications/DebugReceiver.h>
#include <Helpers/DebugMapper.h>
#include <Domain/Constants.h>

namespace vss {

    DebugReceiver::DebugReceiver() {
        address = Address();
    }

    void DebugReceiver::createSocket(TeamType teamType) {
        SetupAddress(teamType);

        context = new zmq::context_t( 1 );
        socket = new zmq::socket_t( *context, ZMQ_PAIR );

        std::cout << "Connecting Client Receiver Debug Team 1: " << address << std::endl;
        socket->bind(address.getFullAddress().c_str());
    }

    Debug DebugReceiver::receiveDebug() {
        vss_debug::Global_Debug globalDebug;

        zmq::message_t request;
        socket->recv( &request );

        std::string msg_str( static_cast<char*>(request.data()), request.size());
        globalDebug.ParseFromString( msg_str );

        return DebugMapper::globalDebugToDebug(globalDebug);
    }

    void DebugReceiver::SetupAddress(TeamType teamType) {
        if(teamType == TeamType::Yellow){
            address = Address(DEFAULT_DEBUG_RECEIVE_ADDRESS, DEFAULT_DEBUG_YELLOW_PORT);
        }else{
            address = Address(DEFAULT_DEBUG_RECEIVE_ADDRESS, DEFAULT_DEBUG_BLUE_PORT);
        }
    }
}