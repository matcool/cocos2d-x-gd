cmake_minimum_required(VERSION 3.25.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cocos2d VERSION 0.1.0)

add_library(cocos2d SHARED
external/chipmunk/src/chipmunk.c
external/chipmunk/src/cpArbiter.c
external/chipmunk/src/cpArray.c
external/chipmunk/src/cpBB.c
external/chipmunk/src/cpBBTree.c
external/chipmunk/src/cpBody.c
external/chipmunk/src/cpCollision.c
external/chipmunk/src/cpHashSet.c
external/chipmunk/src/cpPolyShape.c
external/chipmunk/src/cpShape.c
external/chipmunk/src/cpSpace.c
external/chipmunk/src/cpSpaceComponent.c
external/chipmunk/src/cpSpaceHash.c
external/chipmunk/src/cpSpaceQuery.c
external/chipmunk/src/cpSpaceStep.c
external/chipmunk/src/cpSpatialIndex.c
external/chipmunk/src/cpSweep1D.c
external/chipmunk/src/cpVect.c
external/chipmunk/src/constraints/cpConstraint.c
external/chipmunk/src/constraints/cpDampedRotarySpring.c
external/chipmunk/src/constraints/cpDampedSpring.c
external/chipmunk/src/constraints/cpGearJoint.c
external/chipmunk/src/constraints/cpGrooveJoint.c
external/chipmunk/src/constraints/cpPinJoint.c
external/chipmunk/src/constraints/cpPivotJoint.c
external/chipmunk/src/constraints/cpRatchetJoint.c
external/chipmunk/src/constraints/cpRotaryLimitJoint.c
external/chipmunk/src/constraints/cpSimpleMotor.c
external/chipmunk/src/constraints/cpSlideJoint.c

# CocosDenshion/win32/MciPlayer.cpp
# CocosDenshion/win32/SimpleAudioEngine.cpp

cocos2dx/base_nodes/CCAtlasNode.cpp
cocos2dx/base_nodes/CCNode.cpp
cocos2dx/ccFPSImages.c
cocos2dx/cocoa/CCAffineTransform.cpp
cocos2dx/cocoa/CCArray.cpp
cocos2dx/cocoa/CCAutoreleasePool.cpp
cocos2dx/cocoa/CCDataVisitor.cpp
cocos2dx/cocoa/CCDictionary.cpp
cocos2dx/cocoa/CCGeometry.cpp
cocos2dx/cocoa/CCNS.cpp
cocos2dx/cocoa/CCObject.cpp
cocos2dx/cocoa/CCSet.cpp
cocos2dx/cocoa/CCString.cpp
cocos2dx/cocoa/CCZone.cpp
cocos2dx/draw_nodes/CCDrawingPrimitives.cpp
cocos2dx/draw_nodes/CCDrawNode.cpp
cocos2dx/effects/CCGrabber.cpp
cocos2dx/effects/CCGrid.cpp
cocos2dx/actions/CCAction.cpp
cocos2dx/actions/CCActionCamera.cpp
cocos2dx/actions/CCActionCatmullRom.cpp
cocos2dx/actions/CCActionEase.cpp
cocos2dx/actions/CCActionGrid.cpp
cocos2dx/actions/CCActionGrid3D.cpp
cocos2dx/actions/CCActionInstant.cpp
cocos2dx/actions/CCActionInterval.cpp
cocos2dx/actions/CCActionManager.cpp
cocos2dx/actions/CCActionPageTurn3D.cpp
cocos2dx/actions/CCActionProgressTimer.cpp
cocos2dx/actions/CCActionTiledGrid.cpp
cocos2dx/actions/CCActionTween.cpp
cocos2dx/label_nodes/CCLabelAtlas.cpp
cocos2dx/label_nodes/CCLabelBMFont.cpp
cocos2dx/label_nodes/CCLabelTTF.cpp
cocos2dx/layers_scenes_transitions_nodes/CCLayer.cpp
cocos2dx/layers_scenes_transitions_nodes/CCScene.cpp
cocos2dx/layers_scenes_transitions_nodes/CCTransition.cpp
cocos2dx/layers_scenes_transitions_nodes/CCTransitionPageTurn.cpp
cocos2dx/layers_scenes_transitions_nodes/CCTransitionProgress.cpp
cocos2dx/menu_nodes/CCMenu.cpp
cocos2dx/menu_nodes/CCMenuItem.cpp
cocos2dx/misc_nodes/CCClippingNode.cpp
cocos2dx/misc_nodes/CCMotionStreak.cpp
cocos2dx/misc_nodes/CCProgressTimer.cpp
cocos2dx/misc_nodes/CCRenderTexture.cpp
cocos2dx/particle_nodes/CCParticleBatchNode.cpp
cocos2dx/particle_nodes/CCParticleExamples.cpp
cocos2dx/particle_nodes/CCParticleSystem.cpp
cocos2dx/particle_nodes/CCParticleSystemQuad.cpp
cocos2dx/platform/CCEGLViewProtocol.cpp
cocos2dx/platform/CCFileUtils.cpp
cocos2dx/platform/CCImageCommonWebp.cpp
cocos2dx/platform/CCSAXParser.cpp
cocos2dx/platform/CCThread.cpp
cocos2dx/platform/platform.cpp
cocos2dx/platform/win32/CCAccelerometer.cpp
cocos2dx/platform/win32/CCApplication.cpp
cocos2dx/platform/win32/CCCommon.cpp
cocos2dx/platform/win32/CCDevice.cpp
cocos2dx/platform/win32/CCEGLView.cpp
cocos2dx/platform/win32/CCFileUtilsWin32.cpp
cocos2dx/platform/win32/CCImage.cpp
cocos2dx/platform/win32/CCStdC.cpp
cocos2dx/shaders/CCGLProgram.cpp
cocos2dx/shaders/ccGLStateCache.cpp
cocos2dx/shaders/CCShaderCache.cpp
cocos2dx/shaders/ccShaders.cpp
cocos2dx/sprite_nodes/CCAnimation.cpp
cocos2dx/sprite_nodes/CCAnimationCache.cpp
cocos2dx/sprite_nodes/CCSprite.cpp
cocos2dx/sprite_nodes/CCSpriteBatchNode.cpp
cocos2dx/sprite_nodes/CCSpriteFrame.cpp
cocos2dx/sprite_nodes/CCSpriteFrameCache.cpp
cocos2dx/support/base64.cpp
cocos2dx/support/CCNotificationCenter.cpp
cocos2dx/support/CCPointExtension.cpp
cocos2dx/support/CCProfiling.cpp
cocos2dx/support/ccUTF8.cpp
cocos2dx/support/ccUtils.cpp
cocos2dx/support/CCVertex.cpp
cocos2dx/support/component/CCComponent.cpp
cocos2dx/support/component/CCComponentContainer.cpp
cocos2dx/support/tinyxml2/tinyxml2.cpp
cocos2dx/support/TransformUtils.cpp
cocos2dx/support/data_support/ccCArray.cpp
cocos2dx/support/image_support/TGAlib.cpp
cocos2dx/support/user_default/CCUserDefault.cpp
cocos2dx/support/zip_support/ioapi.cpp
cocos2dx/support/zip_support/unzip.cpp
cocos2dx/support/zip_support/ZipUtils.cpp
cocos2dx/textures/CCTexture2D.cpp
cocos2dx/textures/CCTextureAtlas.cpp
cocos2dx/textures/CCTextureCache.cpp
cocos2dx/textures/CCTextureETC.cpp
cocos2dx/textures/CCTexturePVR.cpp
cocos2dx/tileMap_parallax_nodes/CCParallaxNode.cpp
cocos2dx/tileMap_parallax_nodes/CCTileMapAtlas.cpp
cocos2dx/tileMap_parallax_nodes/CCTMXLayer.cpp
cocos2dx/tileMap_parallax_nodes/CCTMXObjectGroup.cpp
cocos2dx/tileMap_parallax_nodes/CCTMXTiledMap.cpp
cocos2dx/tileMap_parallax_nodes/CCTMXXMLParser.cpp
cocos2dx/touch_dispatcher/CCTouch.cpp
cocos2dx/touch_dispatcher/CCTouchDispatcher.cpp
cocos2dx/touch_dispatcher/CCTouchHandler.cpp
cocos2dx/keypad_dispatcher/CCKeypadDelegate.cpp
cocos2dx/keypad_dispatcher/CCKeypadDispatcher.cpp
cocos2dx/text_input_node/CCIMEDispatcher.cpp
cocos2dx/text_input_node/CCTextFieldTTF.cpp
cocos2dx/script_support/CCScriptSupport.cpp
cocos2dx/kazmath/src/aabb.c
cocos2dx/kazmath/src/mat3.c
cocos2dx/kazmath/src/mat4.c
cocos2dx/kazmath/src/neon_matrix_impl.c
cocos2dx/kazmath/src/plane.c
cocos2dx/kazmath/src/quaternion.c
cocos2dx/kazmath/src/ray2.c
cocos2dx/kazmath/src/utility.c
cocos2dx/kazmath/src/vec2.c
cocos2dx/kazmath/src/vec3.c
cocos2dx/kazmath/src/vec4.c
cocos2dx/kazmath/src/GL/mat4stack.c
cocos2dx/kazmath/src/GL/matrix.c
cocos2dx/CCCamera.cpp
cocos2dx/CCConfiguration.cpp
cocos2dx/CCDirector.cpp
cocos2dx/CCScheduler.cpp
cocos2dx/cocos2d.cpp

cocos2dx/robtop/keyboard_dispatcher/CCKeyboardDispatcher.cpp
cocos2dx/robtop/mouse_dispatcher/CCMouseDispatcher.cpp
cocos2dx/robtop/xml/ObjectDecoder.cpp

# extensions/AssetsManager/AssetsManager.cpp
# extensions/CCBReader/CCBAnimationManager.cpp
# extensions/CCBReader/CCBFileLoader.cpp
# extensions/CCBReader/CCBKeyframe.cpp
# extensions/CCBReader/CCBReader.cpp
# extensions/CCBReader/CCBSequence.cpp
# extensions/CCBReader/CCBSequenceProperty.cpp
# extensions/CCBReader/CCBValue.cpp
# extensions/CCBReader/CCControlButtonLoader.cpp
# extensions/CCBReader/CCControlLoader.cpp
# extensions/CCBReader/CCData.cpp
# extensions/CCBReader/CCLabelBMFontLoader.cpp
# extensions/CCBReader/CCLabelTTFLoader.cpp
# extensions/CCBReader/CCLayerColorLoader.cpp
# extensions/CCBReader/CCLayerGradientLoader.cpp
# extensions/CCBReader/CCLayerLoader.cpp
# extensions/CCBReader/CCMenuItemImageLoader.cpp
# extensions/CCBReader/CCMenuItemLoader.cpp
# extensions/CCBReader/CCNode+CCBRelativePositioning.cpp
# extensions/CCBReader/CCNodeLoader.cpp
# extensions/CCBReader/CCNodeLoaderLibrary.cpp
# extensions/CCBReader/CCParticleSystemQuadLoader.cpp
# extensions/CCBReader/CCScale9SpriteLoader.cpp
# extensions/CCBReader/CCScrollViewLoader.cpp
# extensions/CCBReader/CCSpriteLoader.cpp
# extensions/CocoStudio/Action/CCActionEaseEx.cpp
# extensions/CocoStudio/Action/CCActionFrame.cpp
# extensions/CocoStudio/Action/CCActionFrameEasing.cpp
# extensions/CocoStudio/Action/CCActionManager.cpp
# extensions/CocoStudio/Action/CCActionNode.cpp
# extensions/CocoStudio/Action/CCActionObject.cpp
# extensions/CocoStudio/Armature/animation/CCArmatureAnimation.cpp
# extensions/CocoStudio/Armature/animation/CCProcessBase.cpp
# extensions/CocoStudio/Armature/animation/CCTween.cpp
# extensions/CocoStudio/Armature/CCArmature.cpp
# extensions/CocoStudio/Armature/CCBone.cpp
# extensions/CocoStudio/Armature/datas/CCDatas.cpp
# extensions/CocoStudio/Armature/display/CCBatchNode.cpp
# extensions/CocoStudio/Armature/display/CCDecorativeDisplay.cpp
# extensions/CocoStudio/Armature/display/CCDisplayFactory.cpp
# extensions/CocoStudio/Armature/display/CCDisplayManager.cpp
# extensions/CocoStudio/Armature/display/CCSkin.cpp
# extensions/CocoStudio/Armature/physics/CCColliderDetector.cpp
# extensions/CocoStudio/Armature/utils/CCArmatureDataManager.cpp
# extensions/CocoStudio/Armature/utils/CCArmatureDefine.cpp
# extensions/CocoStudio/Armature/utils/CCDataReaderHelper.cpp
# extensions/CocoStudio/Armature/utils/CCSpriteFrameCacheHelper.cpp
# extensions/CocoStudio/Armature/utils/CCTransformHelp.cpp
# extensions/CocoStudio/Armature/utils/CCTweenFunction.cpp
# extensions/CocoStudio/Armature/utils/CCUtilMath.cpp
# extensions/CocoStudio/Components/CCComAttribute.cpp
# extensions/CocoStudio/Components/CCComAudio.cpp
# extensions/CocoStudio/Components/CCComController.cpp
# extensions/CocoStudio/Components/CCComRender.cpp
# extensions/CocoStudio/Components/CCInputDelegate.cpp
# extensions/CocoStudio/GUI/BaseClasses/UIWidget.cpp
# extensions/CocoStudio/GUI/Layouts/UILayout.cpp
# extensions/CocoStudio/GUI/Layouts/UILayoutDefine.cpp
# extensions/CocoStudio/GUI/Layouts/UILayoutParameter.cpp
# extensions/CocoStudio/GUI/System/CocosGUI.cpp
# extensions/CocoStudio/GUI/System/UIHelper.cpp
# extensions/CocoStudio/GUI/System/UITouchGroup.cpp
# extensions/CocoStudio/GUI/UIWidgets/ScrollWidget/UIListView.cpp
# extensions/CocoStudio/GUI/UIWidgets/ScrollWidget/UIPageView.cpp
# extensions/CocoStudio/GUI/UIWidgets/ScrollWidget/UIScrollView.cpp
# extensions/CocoStudio/GUI/UIWidgets/UIButton.cpp
# extensions/CocoStudio/GUI/UIWidgets/UICheckBox.cpp
# extensions/CocoStudio/GUI/UIWidgets/UIImageView.cpp
# extensions/CocoStudio/GUI/UIWidgets/UILabel.cpp
# extensions/CocoStudio/GUI/UIWidgets/UILabelAtlas.cpp
# extensions/CocoStudio/GUI/UIWidgets/UILabelBMFont.cpp
# extensions/CocoStudio/GUI/UIWidgets/UILoadingBar.cpp
# extensions/CocoStudio/GUI/UIWidgets/UIRichText.cpp
# extensions/CocoStudio/GUI/UIWidgets/UISlider.cpp
# extensions/CocoStudio/GUI/UIWidgets/UITextField.cpp
# extensions/CocoStudio/Json/DictionaryHelper.cpp
# extensions/CocoStudio/Reader/GUIReader.cpp
# extensions/CocoStudio/Reader/SceneReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/ButtonReader/ButtonReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/CheckBoxReader/CheckBoxReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/ImageViewReader/ImageViewReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/LabelAtlasReader/LabelAtlasReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/LabelBMFontReader/LabelBMFontReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/LabelReader/LabelReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/LayoutReader/LayoutReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/ListViewReader/ListViewReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/LoadingBarReader/LoadingBarReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/PageViewReader/PageViewReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/ScrollViewReader/ScrollViewReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/SliderReader/SliderReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/TextFieldReader/TextFieldReader.cpp
# extensions/CocoStudio/Reader/WidgetReader/WidgetReader.cpp
# extensions/CocoStudio/Trigger/ObjectFactory.cpp
# extensions/CocoStudio/Trigger/TriggerBase.cpp
# extensions/CocoStudio/Trigger/TriggerMng.cpp
# extensions/CocoStudio/Trigger/TriggerObj.cpp
extensions/GUI/CCControlExtension/CCControl.cpp
extensions/GUI/CCControlExtension/CCControlButton.cpp
extensions/GUI/CCControlExtension/CCControlColourPicker.cpp
extensions/GUI/CCControlExtension/CCControlHuePicker.cpp
extensions/GUI/CCControlExtension/CCControlPotentiometer.cpp
extensions/GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp
extensions/GUI/CCControlExtension/CCControlSlider.cpp
extensions/GUI/CCControlExtension/CCControlStepper.cpp
extensions/GUI/CCControlExtension/CCControlSwitch.cpp
extensions/GUI/CCControlExtension/CCControlUtils.cpp
extensions/GUI/CCControlExtension/CCInvocation.cpp
extensions/GUI/CCControlExtension/CCScale9Sprite.cpp
# extensions/GUI/CCEditBox/CCEditBox.cpp
# extensions/GUI/CCEditBox/CCEditBoxImplWin.cpp
# extensions/GUI/CCScrollView/CCScrollView.cpp
# extensions/GUI/CCScrollView/CCSorting.cpp
# extensions/GUI/CCScrollView/CCTableView.cpp
# extensions/GUI/CCScrollView/CCTableViewCell.cpp
# extensions/LocalStorage/LocalStorage.cpp
# extensions/network/HttpClient.cpp
# extensions/network/Websocket.cpp
# extensions/physics_nodes/CCPhysicsDebugNode.cpp
# extensions/physics_nodes/CCPhysicsSprite.cpp
# extensions/spine/Animation.cpp
# extensions/spine/AnimationState.cpp
# extensions/spine/AnimationStateData.cpp
# extensions/spine/Atlas.cpp
# extensions/spine/AtlasAttachmentLoader.cpp
# extensions/spine/Attachment.cpp
# extensions/spine/AttachmentLoader.cpp
# extensions/spine/Bone.cpp
# extensions/spine/BoneData.cpp
# extensions/spine/CCSkeleton.cpp
# extensions/spine/CCSkeletonAnimation.cpp
# extensions/spine/extension.cpp
# extensions/spine/Json.cpp
# extensions/spine/RegionAttachment.cpp
# extensions/spine/Skeleton.cpp
# extensions/spine/SkeletonData.cpp
# extensions/spine/SkeletonJson.cpp
# extensions/spine/Skin.cpp
# extensions/spine/Slot.cpp
# extensions/spine/SlotData.cpp
# extensions/spine/spine-cocos2dx.cpp
# extensions/proj.win32/Win32InputBox.cpp

# samples/Cpp/HelloCpp/proj.win32/main.cpp
# samples/Cpp/HelloCpp/Classes/AppDelegate.cpp
# samples/Cpp/HelloCpp/Classes/HelloWorldScene.cpp
)

target_include_directories(cocos2d PUBLIC
external

CocosDenshion/include

external/chipmunk/include/chipmunk

cocos2dx
cocos2dx/include
cocos2dx/kazmath/include
cocos2dx/platform/win32
cocos2dx/platform/third_party/win32
cocos2dx/platform/third_party/win32/OGLES
cocos2dx/platform/third_party/win32/zlib
cocos2dx/platform/third_party/win32/pthread
cocos2dx/platform/third_party/win32/libpng
cocos2dx/platform/third_party/win32/curl
cocos2dx/platform/third_party/win32/libjpeg
cocos2dx/platform/third_party/win32/iconv
cocos2dx/platform/third_party/win32/libwebp
extensions
)

target_link_libraries(cocos2d PRIVATE
opengl32
${CMAKE_CURRENT_SOURCE_DIR}/cocos2dx/platform/third_party/win32/libraries/glew32.lib
${CMAKE_CURRENT_SOURCE_DIR}/cocos2dx/platform/third_party/win32/libraries/libwebp.lib
${CMAKE_CURRENT_SOURCE_DIR}/cocos2dx/platform/third_party/win32/libraries/pthreadVC2.lib
${CMAKE_CURRENT_SOURCE_DIR}/cocos2dx/platform/third_party/win32/libraries/zlibstatic.lib
${CMAKE_CURRENT_SOURCE_DIR}/cocos2dx/platform/third_party/win32/libraries/libpng16_static.lib
${CMAKE_CURRENT_SOURCE_DIR}/cocos2dx/platform/third_party/win32/libraries/jpeg.lib
${CMAKE_CURRENT_SOURCE_DIR}/cocos2dx/platform/third_party/win32/libraries/glfw3.lib

Winmm.lib
)

# disable the "needs to have dll-interface" warning
if (MSVC)
	target_compile_options(cocos2d PRIVATE /wd4251 /wd4267 /wd4244 /wd4996 /wd4302 /wd4311 /wd4312)
else()
	target_compile_options(cocos2d PRIVATE -Wno-deprecated-declarations)
endif()
# target_compile_definitions(cocos2d PRIVATE HAVE_STRUCT_TIMESPEC CC_ENABLE_BOX2D_INTEGRATION COCOS2D_DEBUG=1)
target_compile_definitions(cocos2d PUBLIC CC_TARGET_OS_WIN32=1 GEODE_IS_MEMBER_TEST=1)
target_compile_definitions(cocos2d PRIVATE HAVE_STRUCT_TIMESPEC COCOS2D_DEBUG=1 _USRDLL=1 CC_TARGET_OS_WIN32=1 GEODE_IS_MEMBER_TEST=1 _AMD64_=1)

target_link_options(cocos2d PRIVATE -Wl,/errorlimit:0)

if (PROJECT_IS_TOP_LEVEL)
	add_subdirectory(mat-sample)
endif()