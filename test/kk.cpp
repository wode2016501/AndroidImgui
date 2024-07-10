#include "ANativeWindowCreator.h"
#include "GraphicsManager.h"
#include "my_imgui.h"
#include "TouchHelperA.h"

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
extern "C" {
void usleep(int); 
int read(int a,char *b,int c);
int lseek(int a,int b,int c);  
}
int main() {
    auto display = android::ANativeWindowCreator::GetDisplayInfo();
    if (display.height > display.width) {
        std::swap(display.height, display.width);
    }
    auto window = android::ANativeWindowCreator::Create("test", display.width, display.width);
    auto graphics = GraphicsManager::getGraphicsInterface(GraphicsManager::VULKAN);

    graphics->Init(window, display.width, display.width);
    ImGui::Android_LoadSystemFont(26);
    Touch::Init({(float) display.width, (float) display.height}, true);

    //auto image = graphics->LoadTextureFromFile("/sdcard/1.png");

    static bool flag = true;
    int fd = open("/sys/class/drm/sde-crtc-0/measured_fps", 0);
    if(fd<0) {
	    printf("错误\n"); 
	    return 1;
    }
#if 0
    char  *mappedData =(char *)  mmap(NULL, 9, 0/*PROT_READ | PROT_WRITE*/ , MAP_SHARED, fd, 0);

    if (mappedData == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
#endif 
    char mappedData[20]; 
    while (flag) {
        graphics->NewFrame();
    //    Touch::setOrientation(android::ANativeWindowCreator::GetDisplayInfo().orientation);
   //     ImGui::SetNextWindowSize({500, 500}, ImGuiCond_Once);
 #if  0
        if (ImGui::Begin("test", &flag)) {
            ImGui::Text("Hello, world!");
           // ImGui::Image(image->DS, {100, 100});
        }
#endif
	ImGui::SetNextWindowSize({120, 1}, ImGuiCond_Once);
        ImGui::Begin("My Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImVec4 redColor = { 0.5f, 0.5f, 0.5f, 0.5f };  //灰色透明
	ImGui::PushStyleColor(ImGuiCol_WindowBg, redColor);
	read(fd,mappedData,8); 
	lseek(fd, 0, 0); 
	mappedData[8]=0;
	//printf("%s\n",mappedData); 
	ImGui::Text("%s",mappedData); 
	usleep(100000); 
        ImGui::End();
        graphics->EndFrame();
    }
   // graphics->DeleteTexture(image);
    graphics->Shutdown();
    return 0;
}
