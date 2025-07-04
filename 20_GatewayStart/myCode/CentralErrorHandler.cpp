
#include "CentralErrorHandler.h"
using namespace std;
// 1. Define constants for the maximum number of ports per system
#define PORT_ASCLINMAX 4
#define PORT_CANNMAX 2




void CentralErrorHandler::terminate() {
	cerr << "Application terminated due to error." << endl;
	exit(EXIT_FAILURE);
}

void CentralErrorHandler::handlePortError() {
	cerr << "Error: Exceeded maximum number of ports per system." << endl;
	terminate();
}

void CentralErrorHandler::handleNullPointerError() {
	cerr << "Error: Null pointer detected." << endl;
	terminate();
}

void CentralErrorHandler::handleOccupiedPortError() {
	cerr << "Error: Port is already in use." << endl;
	throw exception(); // This will trigger the C++ exception handler
}

void CentralErrorHandler::CentralErrorHandler::checkMaxPorts(int asclinCount, int cannCount) {

	if (asclinCount > PORT_ASCLINMAX || cannCount > PORT_CANNMAX) {
		handlePortError();
	}
}


