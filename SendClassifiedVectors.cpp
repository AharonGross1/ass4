/**
 * A class meant to send a vector of Vectors to the client.
 */
#include "SendClassifiedVectors.h"

/**
 * Send all the vectors through a given defaultIO.
 * @param data - The data to send.
 * @param dio - The DefaultIo to send the info through.
 * @param createFile - Flag to
 */
void SendClassifiedVectors::sendVectors(Data *data, DefaultIO *dio, bool createFile){
    // Not all info is valid
    if (data->classifiedFile.empty() or data->unclassifiedFile.empty()){
        dio->write("Upload the data please.");
        dio->read();
        return;
    }
    // Data still isn't classified
    if (data->classificationVector->empty()){
        dio->write("Classify the data please.");
        dio->read();
        return;
    }
    // Get path for file
    if (createFile) {
        dio->write("Enter path");
        dio->read();
        dio->write(dio->sendAnswer);
        std::string csvPathToWrite= dio->read();

        dio->write("Sending data...");
        dio->read();
        dio->write(dio->sendAnswer);
        dio->write(csvPathToWrite);
        dio->read();
    }

    // Send all the data
    int size=sizeof(data->classificationVector);
    std::string classificationToSend;
    for (int i = 0; i < size; i++){
        dio->write(std::to_string(i + 1)+"  "+ *(data->classificationVector->at(i)));
        dio->read();
    }
    // Let client know he needs to close the file.
    if (createFile) {
        dio->write(dio->sendAnswer);
    }
    dio->write("Done sending the vector Classifications.");
    dio->read();
}