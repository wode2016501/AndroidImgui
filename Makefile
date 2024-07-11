CXXFLAGS=-O2 -g -DNDEBUG -std=gnu++20  -DIMGUI_IMPL_VULKAN_NO_PROTOTYPES -DVK_USE_PLATFORM_ANDROID_KHR
CPPFLAGS=-I. -Iimgui -Isrc -Istb -Iimgui/backends
LDFLAGS= -L. 
CXX=c++
LIB_OBJS = stb/stb_image.o imgui/imgui.o imgui/imgui_draw.o imgui/imgui_widgets.o imgui/imgui_tables.o imgui/imgui_demo.o imgui/backends/imgui_impl_opengl3.o imgui/backends/imgui_impl_vulkan.o

test_OBJS = test/main.o test/TouchHelperA.o

src_OBJS= src/AndroidImgui.o src/GraphicsManager.o src/OpenGLGraphics.o src/VulkanGraphics.o src/my_imgui.o src/my_imgui_impl_android.o src/vulkan_wrapper.o

LIB_NAME = libAndroidImgui.a

LIBS= -llog -landroid -lEGL -lGLESv3 -lz -lm -lAndroidImgui

all: AndroidImgui

$(LIB_NAME): $(LIB_OBJS)
	$(AR) r $@ $^ 
AndroidImgui: $(test_OBJS) $(src_OBJS) $(LIB_NAME)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)
	
clean:
	$(RM) $(LIB_OBJS)
	$(RM) $(test_OBJS)
	$(RM) $(src_OBJS)
