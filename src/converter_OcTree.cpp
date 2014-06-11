#include <boost/shared_ptr.hpp>
#include <rsb/Factory.h>
#include <rsb/converter/Repository.h>
#include <rsb/Event.h>
#include <rsb/Handler.h>
#include <rsb/filter/OriginFilter.h>
#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include "OcTreeConverter.h"            // This is the converter
#include <string>

using namespace boost;
using namespace std;
using namespace octomap;
using namespace rsb;
using namespace rsb::converter;
using namespace converter_OcTree;

// Filling the octree with some data
void createTree(OcTree * tree);

// Print out the recieved octree
void getMessage(rsb::EventPtr event);

//// Simple sending of an octree
//int main() {
//    // Register our converter within the collection of converters for
//    // the string wire-type (which is used for arrays of octets in
//    // C++).
//    shared_ptr<OcTreeConverter> converter(new OcTreeConverter());
//    converterRepository<std::string>()->registerConverter(converter);
//
//    // Create an Informer object that is parametrized with the
//    // data-type SimpleImage.
//
//    Informer<OcTree>::Ptr informer =
//            getFactory().createInformer<OcTree> (
//                    Scope("/octree"));
//
//    // Construct and send a OcTree object.
//    shared_ptr<OcTree> tree(new OcTree(0.1));
//    informer->publish(tree);
//
//    return EXIT_SUCCESS;
//}


// Sending and receiving of an octree
int main(int argc, char *argv[]) {

    // Register our converter within the collection of converters for
    // the string wire-type (which is used for arrays of octets in
    // C++).
    shared_ptr<OcTreeConverter> converter(new OcTreeConverter());
    converterRepository<std::string>()->registerConverter(converter);


    rsb::Factory &factory = rsb::Factory::getInstance();


    // Create the informer
    Informer<OcTree>::Ptr informer =
            getFactory().createInformer<OcTree> (Scope("/pointcloud"));

    // Create and start the listener
    rsb::ListenerPtr listener = factory.createListener("/pointcloud");
    listener->addHandler(rsb::HandlerPtr(new rsb::EventFunctionHandler(&getMessage)));


    // Create an octree with 0.1 resolution and fill it with some data
    shared_ptr<OcTree> message(new OcTree(0.1));
    createTree( &(*message) );


    // Hit enter to send an octree
    while (true) {
    	// Keyboard input
        cout << "Hit enter for sending an octree or ^C for exit" << endl;
        cout.flush();
        string keyboard;
        getline(cin, keyboard); // This blocks until enter was hit

        cout << "Write send message to 'input.bt'" << endl;
        message->writeBinary("input.bt");

        // Publish the data
        informer->publish(message);
    }

    return EXIT_SUCCESS;
}



void createTree(OcTree * tree) {
	  cout << "generating example map" << endl;

	  // insert some measurements of occupied cells

	  for (int x=-20; x<20; x++) {
	    for (int y=-20; y<20; y++) {
	      for (int z=-20; z<20; z++) {
	        point3d endpoint ((float) x*0.05f, (float) y*0.05f, (float) z*0.05f);
	        tree->updateNode(endpoint, true); // integrate 'occupied' measurement
	      }
	    }
	  }

	  // insert some measurements of free cells

	  for (int x=-30; x<30; x++) {
	    for (int y=-30; y<30; y++) {
	      for (int z=-30; z<30; z++) {
	        point3d endpoint ((float) x*0.02f-1.0f, (float) y*0.02f-1.0f, (float) z*0.02f-1.0f);
	        tree->updateNode(endpoint, false);  // integrate 'free' measurement
	      }
	    }
	  }
}

void getMessage(rsb::EventPtr event) {

	// Get the data
    shared_ptr<OcTree> message_rec = static_pointer_cast<OcTree>(event->getData());

    // Write OcTree to file
    message_rec->writeBinary("output.bt");

    // Some output
	cout << endl << "Write recieved date to 'output.bt'" << endl;
    cout.flush();
}

