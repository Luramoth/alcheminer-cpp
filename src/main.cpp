#include <cstdlib>
#include <iostream>

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRTShaderSystem.h>

class KeyHandler : public OgreBites::InputListener {
    bool keyPressed(const OgreBites::KeyboardEvent& evt) override {
        if (evt.keysym.sym == OgreBites::SDLK_ESCAPE) {
            Ogre::Root::getSingleton().queueEndRendering();
        }
        return true;
    }
};

int main() {
    std::cout << "Hello World!\n";

    OgreBites::ApplicationContext ctx("Alcheminer");
    ctx.initApp();

    // get pointer to the already made root
    Ogre::Root* root = ctx.getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager();

    // register the scene with RTSS
    Ogre::RTShader::ShaderGenerator* shaderGen =  Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shaderGen->addSceneManager(scnMgr);

    // let there be light
    Ogre::Light* light = scnMgr->createLight("MainLight");
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 0, 15);
    lightNode->attachObject(light);

    // also need to tell Ogre where we are
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5);
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);

    // tell it to render into the scene view
    ctx.getRenderWindow()->addViewport(cam);

    // add something to render
    Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);

    // reister for input events
    KeyHandler keyHandler;
    ctx.addInputListener(&keyHandler);

    ctx.getRoot()->startRendering();
    ctx.closeApp();

    return EXIT_SUCCESS;
}
