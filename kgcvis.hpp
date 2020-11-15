#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

class KGCVIS{
    private:
    std::vector<std::stringstream>pages;
    bool drawFlag;
    public:
    const int width, height;
    KGCVIS(int width = 640, int height = 480):width(width), height(height){pages.resize(1);drawFlag = false;};
    void newPage();
    void drawCircle(int x, int y, int r, int R, int G, int B, int thickness);
    void drawBox(int x1, int y1, int x2, int y2, int R, int G, int B, int thickness);
    void drawLine(int x1, int y1, int x2, int y2, int R, int G, int B, int thickness);
    void drawString(int x, int y, int size, std::string str, int R, int G, int B);
    void drawArrow(int fromX, int fromY, int toX, int toY, int R, int G, int B, int thickness);
    void write(std::string filename = "result.html", std::string title = "kgcvis");
};

void KGCVIS::newPage() {
    pages.resize(pages.size() + 1);
    drawFlag = false;
}

void KGCVIS::drawCircle(int x, int y, int r, int R, int G, int B, int thickness) {
    pages.back() << "drawCircle(" << x << "," << y << "," << r << "," << thickness << "," << R << "," << G << "," << B << ");";
    drawFlag = true;
}

void KGCVIS::drawBox(int x1, int y1, int x2, int y2, int R, int G, int B, int thickness) {
    pages.back() << "drawBox(" << x1 << "," << y1 << "," << x2 << "," << y2 <<","<< thickness << "," << R << "," << G << "," << B << ");";
    drawFlag = true;
}
void KGCVIS::drawLine(int x1, int y1, int x2, int y2, int R, int G, int B, int thickness) {
    pages.back() << "drawLine(" << x1 << "," << y1 << "," << x2 << "," << y2 <<","<< thickness << "," << R << "," << G << "," << B << ");";
    drawFlag = true;
}
void KGCVIS::drawString(int x, int y, int size, std::string str, int R, int G, int B) {
    pages.back() << "drawString(" << x << "," << y << "," << size << ",'" << str << "'," << R << "," << G << "," << B << ");";
    drawFlag = true;
}
void KGCVIS::drawArrow(int fromX, int fromY, int toX, int toY, int R, int G, int B, int thickness) {
    double rad = std::atan2(fromY - toY, fromX - toX);
	double length = std::hypot(fromY - toY, fromX - toX);
	std::stringstream ss;
	pages.back() << "drawLine(" << fromX << "," << fromY << "," << toX << "," << toY << "," << thickness << "," << R << "," << G << "," << B << ");";
	pages.back() << "drawLine(" << toX + std::cos(rad + 0.3)*length*0.2 << "," << toY + std::sin(rad + 0.3)*length*0.2 << "," << toX << "," << toY << "," << thickness << "," << R << "," << G << "," << B << ");";
	pages.back() << "drawLine(" << toX + std::cos(rad - 0.3)*length*0.2 << "," << toY + std::sin(rad - 0.3)*length*0.2 << "," << toX << "," << toY << "," << thickness << "," << R << "," << G << "," << B << ");";
    drawFlag = true;
}


void KGCVIS::write(std::string filename, std::string title) {

    int pageNum = pages.size();
    if (drawFlag == false) {
        pageNum--;
    }

    std::ofstream ofs(filename);
    ofs << "<html><head><title>" << title << "</title>" << std::endl;
    
    ofs << "<script type='text/javascript'>" << std::endl;
    ofs << "let canvas, ctx, pageNow = 1, pageNum = " << pageNum << ", lastPage = -1, cnt = 0;" << std::endl;
    ofs << "window.onload = function(){" << std::endl;
    ofs << "canvas = document.getElementById('kgcvis');" << std::endl;
    ofs << "ctx = canvas.getContext('2d');" << std::endl;
    ofs << "canvas.height = " << height << ";" << std::endl;
    ofs << "canvas.width = " << width << ";" << std::endl;
    ofs << "update();};" << std::endl;

    //rgb(r,g,b);
    ofs << "function rgb(r, g, b){return 'rgb('+r+','+g+','+b+')';}" << std::endl;

    //drawCircle(x, y, radius. thickness, R, G, B);
    ofs << "function drawCircle(x, y, radius, thickness, R, G, B){" << std::endl;
    ofs << "if (thickness < 0){" << std::endl;
    ofs << "ctx.fillStyle=rgb(R,G,B);ctx.beginPath();ctx.arc(x, y, radius, 0, Math.PI * 2, true);ctx.fill();" << std::endl;
    ofs << "}" << std::endl;
    ofs << "else{" << std::endl;
    ofs << "ctx.strokeStyle = rgb(R,G,B);ctx.lineWidth = thickness;ctx.beginPath();ctx.arc(x, y, radius, 0, Math.PI * 2, false);ctx.stroke();" << std::endl;
    ofs << "}" << std::endl;
    ofs << "}" << std::endl;

    //drawBox(x1, y1, x2, y2, thickness, R, G, B);
    ofs << "function drawBox(x1, y1, x2, y2, thickness, R, G, B){" << std::endl;
    ofs << "var w=x2-x1, h=y2-y1;" << std::endl;
    ofs << "if(thickness<0){" << std::endl;
    ofs << "ctx.fillStyle=rgb(R,G,B);ctx.fillRect(x1, y1, w, h);" << std::endl;
    ofs << "}" << std::endl;
    ofs << "else{" << std::endl;
    ofs << "ctx.lineWidth=thickness;ctx.strokeStyle=rgb(R,G,B);ctx.strokeRect(x1, y1, w, h);" << std::endl;
    ofs << "}" << std::endl;
    ofs << "}" << std::endl;

    //drawLine(x1, y1, x2, y2, thickness, R, G, B);
    ofs << "function drawLine(x1, y1, x2, y2, thickness, R, G, B){" << std::endl;
    ofs << "ctx.lineWidth=thickness;ctx.strokeStyle=rgb(R,G,B);ctx.beginPath();ctx.moveTo(x1, y1);ctx.lineTo(x2, y2);ctx.stroke();" << std::endl;
    ofs << "}" << std::endl;

    //drawString(x, y, size, str, R, G, B);
    ofs << "function drawString(x, y, size, str, R, G, B){" << std::endl;
    ofs << "ctx.font=''+size+'px Unknown Font';ctx.fillStyle=rgb(R,G,B);ctx.fillText(str,x,y+size);" << std::endl;
    ofs << "}" << std::endl;

    //drawPolygon(pts, thickness, R, G, B)
    ofs << "function drawPolygon(pts, thickness, R, G, B){" << std::endl;
    ofs << "if(thickness<0){" << std::endl;
    ofs << "ctx.fillStyle=rgb(R,G,B);ctx.beginPath();ctx.moveTo(pts[0][0], pts[0][1]);" << std::endl;
    ofs << " for(var i = 1; i < pts.length; i++)ctx.lineTo(pts[i][0], pts[i][1]);" << std::endl;
    ofs << "ctx.lineTo(pts[0][0], pts[0][1]);ctx.fill();" << std::endl;
    ofs << "}" << std::endl;
    ofs << "else{" << std::endl;
    ofs << "ctx.lineWidth=thickness;ctx.strokeStyle=rgb(R,G,B);ctx.beginPath();ctx.moveTo(pts[0][0], pts[0][1]);" << std::endl;
    ofs << " for(var i = 1; i < pts.length; i++)ctx.lineTo(pts[i][0], pts[i][1]);" << std::endl;
    ofs << "ctx.lineTo(pts[0][0], pts[0][1]);ctx.stroke();" << std::endl;
    ofs << "}" << std::endl;
    ofs << "}" << std::endl;

    //drawChart(pts, thickness, R, G, B)
    ofs << "function drawChart(pts, thickness, R, G, B){" << std::endl;
    ofs << "ctx.lineWidth=thickness;ctx.strokeStyle=rgb(R,G,B);ctx.beginPath();ctx.moveTo(pts[0][0], pts[0][1]);" << std::endl;
    ofs << "for(var i = 1; i < pts.length; i++)ctx.lineTo(pts[i][0], pts[i][1]);" << std::endl;
    ofs << "ctx.stroke();" << std::endl;
    ofs << "}" << std::endl;

    //update();
    ofs << "function update(){" << std::endl;
    ofs << "cnt = 0;" << std::endl;
    ofs << "lstPage = pageNow;" << std::endl;
    ofs << "document.forms.fm.frame.value = pageNow;" << std::endl;
    ofs << "document.getElementById('stepTxt').innerText = `${pageNow} / ${pageNum} `;" << std::endl;
    ofs << "drawBox(0, 0, " << width << ", " << height << ", -1, 255, 255, 255);" << std::endl;
    for (int i = 0; i < pageNum;i++){
        ofs << "if(pageNow == " << i + 1 << "){";
        for (std::string line; std::getline(pages[i], line); ) {
            ofs << line << std::endl;
        }
        ofs << "}" << std::endl;
    }
    ofs << "}" << std::endl;

    //b0();
    ofs << "function b0(){pageNow=1;update();}" << std::endl;

    //b1();
    ofs << "function b1(){" << std::endl;
    ofs << "if(pageNow>1){pageNow--;update();}" << std::endl;
    ofs << "else if(document.forms.fm.loopCheck.checked){pageNow=pageNum;update();}" << std::endl;
    ofs << "}" << std::endl;

    //b2();
    ofs << "function b2(){" << std::endl;
    ofs << "if(pageNow<pageNum){pageNow++;update();}" << std::endl;
    ofs << "else if(document.forms.fm.loopCheck.checked){pageNow=1;update();}" << std::endl;
    ofs << "}" << std::endl;

    //b3();
    ofs << "function b3(){pageNow=pageNum;update();}" << std::endl;

    //loop
    ofs << "function loop(){" << std::endl;
    ofs << "var flg = 0;" << std::endl;
    ofs << "if(lstPage != document.forms.fm.frame.value){" << std::endl;
    ofs << "flg = 1;" << std::endl;
    ofs << "pageNow = document.forms.fm.frame.value;" << std::endl;
    ofs << "}" << std::endl;
    ofs << "else if((++cnt) > (10 - document.forms.fm.speed.value)){" << std::endl;
    ofs << "flg = 1" << std::endl;
    ofs << "if(document.forms.fm.autoCheck.checked){" << std::endl;
    ofs << "pageNow++;" << std::endl;
    ofs << "if(pageNow>pageNum && document.forms.fm.loopCheck.checked)pageNow = 1;" << std::endl;
    ofs << "if(pageNow>pageNum)pageNow = pageNum;" << std::endl;
    ofs << "}" << std::endl;
    ofs << "}" << std::endl;
    ofs << "if(flg && pageNum > 0)update();" << std::endl;
    ofs << "}" << std::endl;
    ofs << "setInterval(loop, 50);" << std::endl;

    ofs << "</script>" << std::endl;
    
    ofs << "</head><body>" << std::endl;
    ofs << "<form name = 'fm'>";
    ofs << "step : <input type='range' name = 'frame' id='range' min='1' max='" << pageNum << "' step='1' value='1' />";
    ofs << "<span id = 'stepTxt'>hoge</span>";
	ofs << "<input type='button' value='|<' onclick='b0();'/>";
	ofs << "<input type='button' value='<' onclick='b1();'/>";
	ofs << "<input type='button' value='>' onclick='b2();'/>";
	ofs << "<input type='button' value='>|' onclick='b3();'/>";
    ofs << "<br>";
	ofs << "(<input name='autoCheck' type='checkbox' checked='true'/>auto) ";
	ofs << "(<input name='loopCheck' type='checkbox' checked='true'/>loop) ";
    ofs << "speed : <input type='range' name='speed' min='1' max='10' step='1' value='10' />";
    ofs << "</form><br><canvas id='kgcvis'></canvas></body></html>";
}
