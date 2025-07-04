// Standard (system) header files
#include <iostream>
#include <stdlib.h>
#include <memory> // For std::unique_ptr
#include <stdexcept> // For std::runtime_error
// Add more standard header files as required
// #include <string>

using namespace std;

// Add your project's header files here
#include "CGateway.h"
#include "CPortFactory.h"
#include "CPort.h"

// Main program
int main() {


	CGateway simpleGateway(CPortFactory::UART, CPortFactory::CAN);
	simpleGateway.transmitFromAToB();


	try {

		// Get user input for port types
		int portType1, portType2;
		cout << "Enter port type for Port 1 (0 for UART, 1 for CAN): ";
		cin >> portType1;
		cout << "Enter port type for Port 2 (0 for UART, 1 for CAN): ";
		cin >> portType2;

		// Create ports based on user input
		unique_ptr<CPort> Port1(CPortFactory::createPort(static_cast<CPortFactory::port_t>(portType1)));
		unique_ptr<CPort> Port2(CPortFactory::createPort(static_cast<CPortFactory::port_t>(portType2)));


		CentralErrorHandler errorHandler;

		// Initialize Gateway with ports and error handler
		CGateway gateway(*Port1, *Port2, errorHandler);
		gateway.transmitFromAToB();
	} catch (const exception& e) {
		cerr << "Caught exception: " << e.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
