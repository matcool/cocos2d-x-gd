/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCEGLView.h"
#include "cocoa/CCSet.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "text_input_node/CCIMEDispatcher.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "support/CCPointExtension.h"
#include "CCApplication.h"
#include "robtop/keyboard_dispatcher/CCKeyboardDispatcher.h"
#include "robtop/mouse_dispatcher/CCMouseDispatcher.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include "robtop/glfw/glfw3native.h"

NS_CC_BEGIN

static bool glew_dynamic_binding()
{
	const char *gl_extensions = (const char*)glGetString(GL_EXTENSIONS);

	// If the current opengl driver doesn't have framebuffers methods, check if an extension exists
	if (glGenFramebuffers == NULL)
	{
		CCLog("OpenGL: glGenFramebuffers is NULL, try to detect an extension");
		if (strstr(gl_extensions, "ARB_framebuffer_object"))
		{
			CCLog("OpenGL: ARB_framebuffer_object is supported");

			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbuffer");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbuffer");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffers");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffers");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorage");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameteriv");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebuffer");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebuffer");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffers");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffers");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatus");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1D");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2D");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3D");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbuffer");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmap");
		}
		else
		if (strstr(gl_extensions, "EXT_framebuffer_object"))
		{
			CCLog("OpenGL: EXT_framebuffer_object is supported");
			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbufferEXT");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbufferEXT");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffersEXT");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffersEXT");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorageEXT");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameterivEXT");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebufferEXT");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebufferEXT");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffersEXT");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffersEXT");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatusEXT");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1DEXT");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2DEXT");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3DEXT");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbufferEXT");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmapEXT");
		}
		else
		{
			CCLog("OpenGL: No framebuffers extension is supported");
			CCLog("OpenGL: Any call to Fbo will crash!");
			return false;
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
// impliment CCEGLView
//////////////////////////////////////////////////////////////////////////

CCEGLView::CCEGLView()
: m_bCaptured(false)
// , m_hWnd(NULL)
// , m_hDC(NULL)
// , m_hRC(NULL)
// , m_lpfnAccelerometerKeyHook(NULL)
// , m_menu(NULL)
// , m_wndproc(NULL)
, m_pMainWindow(NULL)
, m_pPrimaryMonitor(NULL)
, m_fFrameZoomFactor(1.0f)
, m_bSupportTouch(false)
{
    strcpy(m_szViewName, "Cocos2dxWin32");
}

CCEGLView::~CCEGLView()
{

}

bool CCEGLView::isOpenGLReady()
{
    return !!m_pMainWindow;
}

void CCEGLView::end()
{
    if (m_pMainWindow) {
        glfwDestroyWindow(m_pMainWindow);
        m_pMainWindow = NULL;
    }
    // glfwTerminate();
    delete this;
}

void CCEGLView::swapBuffers()
{
    if (m_pMainWindow) {
        glfwSwapBuffers(m_pMainWindow);
    }
}


void CCEGLView::setIMEKeyboardState(bool /*bOpen*/)
{

}

void CCEGLView::resizeWindow(int width, int height)
{
    if (m_pMainWindow) {
        glfwSetWindowSize(m_pMainWindow, width, height);
    }
}

void CCEGLView::setFrameZoomFactor(float fZoomFactor)
{
    m_fFrameZoomFactor = fZoomFactor;
    // resize(m_obScreenSize.width * fZoomFactor, m_obScreenSize.height * fZoomFactor);
    // centerWindow();
    // CCDirector::sharedDirector()->setProjection(CCDirector::sharedDirector()->getProjection());
    updateFrameSize();
}

float CCEGLView::getFrameZoomFactor()
{
    return m_fFrameZoomFactor;
}

void CCEGLView::setFrameSize(float width, float height)
{
    CCEGLViewProtocol::setFrameSize(width, height);

    updateFrameSize();
}

void CCEGLView::centerWindow()
{
    if (!m_pMainWindow) {
        return;
    }

    glfwSetWindowPos(m_pMainWindow, 10, 10);
}

void CCEGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(x * m_fScaleX * m_fFrameZoomFactor + m_obViewPortRect.origin.x * m_fFrameZoomFactor),
        (GLint)(y * m_fScaleY  * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
        (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor),
        (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor));
}

void CCEGLView::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * m_fScaleX * m_fFrameZoomFactor + m_obViewPortRect.origin.x * m_fFrameZoomFactor),
              (GLint)(y * m_fScaleY * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
              (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor),
              (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor));
}

CCEGLView* CCEGLView::sharedOpenGLView() {
    return CCDirector::get()->getOpenGLView();
}

CCEGLView* CCEGLView::create(const std::string& name) {
    return createWithRect(name, {0, 0, 960, 640}, 1.0f);
}

CCEGLView* CCEGLView::createWithRect(const std::string& name, cocos2d::CCRect rect, float unk) {
    auto view = new CCEGLView();
    view->initWithRect(name, rect, unk);
    return view;
}

bool CCEGLView::initWithRect(const std::string& name, cocos2d::CCRect rect, float unk) {
    if (!glfwInit()) {
        return false;
    }

    m_pMainWindow = glfwCreateWindow(rect.size.width, rect.size.height, name.c_str(), NULL, NULL);
    if (!m_pMainWindow) {
        return false;
    }
    this->setFrameSize(rect.size.width, rect.size.height);
    // this->setFrameZoomFactor(unk);

    glfwMakeContextCurrent(m_pMainWindow);

    glfwSetKeyCallback(m_pMainWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        CCEGLView::sharedOpenGLView()->onGLFWKeyCallback(window, key, scancode, action, mods);
    });
    glfwSetMouseButtonCallback(m_pMainWindow, [](GLFWwindow* window, int button, int action, int mods) {
        CCEGLView::sharedOpenGLView()->onGLFWMouseCallBack(window, button, action, mods);
    });
    glfwSetCursorPosCallback(m_pMainWindow, [](GLFWwindow* window, double x, double y) {
        CCEGLView::sharedOpenGLView()->onGLFWMouseMoveCallBack(window, x, y);
    });

    this->initGlew();

    return true;
}

void CCEGLView::onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    bool isKeyDown = action != GLFW_RELEASE;
    bool isKeyRepeat = action == GLFW_REPEAT;

    if (key == GLFW_KEY_BACKSPACE && isKeyDown) {
        CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
    }

    auto* dir = CCDirector::sharedDirector();
    auto* kb = dir->getKeyboardDispatcher();

    static std::unordered_map<int, enumKeyCodes> keyMap = {
        {GLFW_KEY_SPACE, KEY_Space},
        {GLFW_KEY_ESCAPE, KEY_Escape},
        {GLFW_KEY_ENTER, KEY_Enter},
        {GLFW_KEY_TAB, KEY_Tab},
        {GLFW_KEY_BACKSPACE, KEY_Backspace},
        {GLFW_KEY_INSERT, KEY_Insert},
        {GLFW_KEY_DELETE, KEY_Delete},
        {GLFW_KEY_RIGHT, KEY_ArrowRight},
        {GLFW_KEY_LEFT, KEY_ArrowLeft},
        {GLFW_KEY_DOWN, KEY_ArrowDown},
        {GLFW_KEY_UP, KEY_ArrowUp},
        {GLFW_KEY_PAGE_UP, KEY_PageUp},
        {GLFW_KEY_PAGE_DOWN, KEY_PageDown},
        {GLFW_KEY_HOME, KEY_Home},
        {GLFW_KEY_END, KEY_End},
        {GLFW_KEY_CAPS_LOCK, KEY_CapsLock},
        {GLFW_KEY_SCROLL_LOCK, KEY_ScrollLock},
        {GLFW_KEY_NUM_LOCK, KEY_Numlock},
        {GLFW_KEY_PRINT_SCREEN, KEY_PrintScreen},
        {GLFW_KEY_PAUSE, KEY_Pause},
        {GLFW_KEY_F1, KEY_F1},
        {GLFW_KEY_F2, KEY_F2},
        {GLFW_KEY_F3, KEY_F3},
        {GLFW_KEY_F4, KEY_F4},
        {GLFW_KEY_F5, KEY_F5},
        {GLFW_KEY_F6, KEY_F6},
        {GLFW_KEY_F7, KEY_F7},
        {GLFW_KEY_F8, KEY_F8},
        {GLFW_KEY_F9, KEY_F9},
        {GLFW_KEY_F10, KEY_F10},
        {GLFW_KEY_F11, KEY_F11},
        {GLFW_KEY_F12, KEY_F12},
        {GLFW_KEY_F13, KEY_F13},
        {GLFW_KEY_F14, KEY_F14},
        {GLFW_KEY_F15, KEY_F15},
        {GLFW_KEY_F16, KEY_F16},
        {GLFW_KEY_F17, KEY_F17},
        {GLFW_KEY_F18, KEY_F18},
        {GLFW_KEY_F19, KEY_F19},
        {GLFW_KEY_F20, KEY_F20},
        {GLFW_KEY_F21, KEY_F21},
        {GLFW_KEY_F22, KEY_F22},
    };
    
    enumKeyCodes keyCode = KEY_None;
    if (auto it = keyMap.find(key); it != keyMap.end()) {
        keyCode = it->second;
    }
    keyCode = kb->convertKeyCode(keyCode);
    CCLOG("key %d %d %d %d", key, scancode, action, mods);

    // TODO: check ime delegate

    CCDirector::sharedDirector()->getKeyboardDispatcher()->dispatchKeyboardMSG(keyCode, isKeyDown, isKeyRepeat);
}

void CCEGLView::onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int mods) {
    // auto* dir = CCDirector::sharedDirector();
    // auto* mouse = dir->getMouseDispatcher();

    // TODO: some stuff with set window pos??

    int touchID = 0;
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            m_bCaptured = true;
            // TODO: mouse locked stuff
            this->handleTouchesBegin(1, &touchID, &m_fMouseX, &m_fMouseY);
        } else if (action == GLFW_RELEASE) {
            if (m_bCaptured) {
                m_bCaptured = false;
                this->handleTouchesEnd(1, &touchID, &m_fMouseX, &m_fMouseY);
            }
        }
    }
}

void CCEGLView::onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y) {
    float fx = x;
    float fy = y;
    int touchID = 0;

    m_fMouseX = x;
    m_fMouseY = y;

    if (m_bCaptured) {
        this->handleTouchesMove(1, &touchID, &fx, &fy);
    }
}

bool CCEGLView::initGlew() {
    if (glewInit() != GLEW_OK) {
        return false;
    }

    if (!glew_dynamic_binding()) {
        return false;
    }

    return true;
}

void CCEGLView::updateFrameSize() {
    if (m_pMainWindow) {
        glfwSetWindowSize(m_pMainWindow, m_obScreenSize.width, m_obScreenSize.height);
    }
}

bool CCEGLView::windowShouldClose() {
    return m_pMainWindow ? glfwWindowShouldClose(m_pMainWindow) : true;
}

void CCEGLView::pollEvents() {
    double x, y;
    glfwGetCursorPos(m_pMainWindow, &x, &y);
    m_fMouseX = x;
    m_fMouseY = y;

    glfwPollEvents();
}

CCEGLView* CCEGLView::createWithFullScreen(std::string const& name, bool borderless, bool fix) {
    return CCEGLView::create(name);
}
CCSize CCEGLView::getDisplaySize() {
    auto hwnd = glfwGetWin32Window(m_pMainWindow);
    auto monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFOEX mi;
    mi.cbSize = sizeof(mi);
    GetMonitorInfo(monitor, &mi);
    float width = mi.rcMonitor.right - mi.rcMonitor.left;
    float height = mi.rcMonitor.bottom - mi.rcMonitor.top;
    return {width, height};
}
void CCEGLView::makeBorderlessTop() {
    ROB_UNIMPLEMENTED();
}
void CCEGLView::showCursor(bool show) {
    ROB_UNIMPLEMENTED();
}
void CCEGLView::toggleFullScreen(bool, bool, bool) {
    ROB_UNIMPLEMENTED();
}
void CCEGLView::toggleLockCursor(bool) {
    ROB_UNIMPLEMENTED();
}
void CCEGLView::iconify() {
    ROB_UNIMPLEMENTED();
}

bool CCEGLView::getShouldHideCursor() const {
    return m_bShouldHideCursor;
}
bool CCEGLView::getCursorLocked() const {
    return m_bCursorLocked;
}
GLFWwindow* CCEGLView::getWindow() const {
    return m_pMainWindow;
}


NS_CC_END
