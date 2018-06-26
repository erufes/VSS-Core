//
// Created by johnathan on 31/05/18.
//

#include <Communications/ControlReceiver.h>
#include <Helpers/ControlMapper.h>
#include <Domain/Constants.h>

namespace vss {

    ControlReceiver::ControlReceiver() {
        address = Address(DEFAULT_CONTROL_RECEIVE_ADDRESS, DEFAULT_CONTROL_PORT);
    }

    void ControlReceiver::createSocket() {
        context = new zmq::context_t( 1 );
        socket = new zmq::socket_t( *context, ZMQ_SUB );

        std::cout << "Control Receiver Connected: " << address << std::endl;
        socket->connect(address.getFullAddress().c_str());

        socket->setsockopt( ZMQ_SUBSCRIBE, "", 0 );
    }

    Control ControlReceiver::receiveControl() {
        vss_control::User_Control userControl;

        zmq::message_t request;
        socket->recv( &request, 0 );

        std::string msg_str( static_cast<char*>(request.data()), request.size());
        userControl.ParseFromString( msg_str );

        return vss::ControlMapper::userControlToControl(userControl);
    }

}