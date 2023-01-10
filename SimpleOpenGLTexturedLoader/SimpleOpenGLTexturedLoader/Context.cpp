#include "Context.h"

std::shared_ptr<Context> Context::contextInstance(nullptr);


Context* Context::getContext()
{
    //singleton pattern, if timerInstance does not exist create one and return pointer to timerInstance
    //otherwise only return pointer
     if (!contextInstance) {
        contextInstance.reset(new Context());
     }
     return contextInstance.get();

}

Context::Context() {
    scaleFactor = 1;
    width = 1920;
    height = 1080;
    aspectRatio = width / height;
    score = 0;
}
