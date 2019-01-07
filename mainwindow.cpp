#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QMessageBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <Qpalette>
#include <QtDebug>
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QTextEdit>
#include <QTextBrowser>
#include <QGroupBox>//模拟方式显示数值
#include <QSpinBox>//数字
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <QTabWidget>//不介绍不算控件
#include <QCompleter>
#include <QHBoxLayout>
#include <QDebug>
#include <QPixmap>
#include <QString>
#include <QLCDNumber>
#include <QTabWidget>
#include <QPainter>
#include <QBrush>
#include <bits/stdc++.h>
using namespace std;


struct node{
    int from,to,next;
}edge[20001];
int n,m,top;//top是edge的大小
int num_of_tarjan;//给dfn和low数组赋值
int num_of_scg;//Strongly Connected Graph数量
int head[1010],low[1010],dfn[1010];//tarjan模板
int vis[1010];//判断edge是否在队列中
int id[1010];//判断点在哪个强连通图中
vector<int> vec;
vector<int> vvec[1010];
int add[1010];//suodian
queue<int> q;
int graph[310][310];
int linestart;
int type;
int currentX=-100,currentY=-100;
int moveX,moveY;
int _Movestart,_Moveend;
int table[20][20],judge[310];
int isdian;
vector<int> placexy;
vector<pair<int,int> > _line;//线
vector<int> del;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->radioButton_2->setChecked(true);

    ui->radioButton_2->setStyleSheet("QPushButton{font:Bold;font-size:30px;color:white;background-color:rgb(191, 62, 255);border:2px ;border-radius:10px;padding:2px 4px;}""QPushButton:hover{color:white;background-color:rgb(178, 58, 238);}""QPushButton:pressed{color:white;background-color:rgb(154, 50, 205);padding-left:3px;padding-top:3px;}");
    ui->radioButton->setStyleSheet("QPushButton{font:Bold;font-size:30px;color:white;background-color:rgb(191, 62, 255);border:2px ;border-radius:10px;padding:2px 4px;}""QPushButton:hover{color:white;background-color:rgb(178, 58, 238);}""QPushButton:pressed{color:white;background-color:rgb(154, 50, 205);padding-left:3px;padding-top:3px;}");
//    ui->radioButton_3->setStyleSheet("QPushButton{font:Bold;font-size:30px;color:white;background-color:rgb(191, 62, 255);border:2px ;border-radius:10px;padding:2px 4px;}""QPushButton:hover{color:white;background-color:rgb(178, 58, 238);}""QPushButton:pressed{color:white;background-color:rgb(154, 50, 205);padding-left:3px;padding-top:3px;}");

    moveX=-100;
    moveY=-100;
    setWindowTitle("连通图");
    setMinimumSize(1000,800);
    setMaximumSize(1000,800);
    QPushButton *button_s = new QPushButton(this);
    button_s->setStyleSheet("font:Bold;font-size:36px;yellow:white;background-color: rgb(200, 200, 200);border:2px ;"
                            "border-radius:10px;padding:2px 4px;");
    button_s->setGeometry(QRect(780, 100, 170, 50));
    button_s->setText("选择绘图:");

    type=1;

    SelectModeGroup = new QButtonGroup(this);



    setMouseTracking(true);
    memset(table,0,sizeof(table));
}




void MainWindow::paintEvent(QPaintEvent*){

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);



    QBrush brush;
    brush.setColor(QColor(255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    p.setBrush(brush);



    QPen pen=p.pen();
    p.setPen(pen);
    p.drawRect(30, 30, 740, 740 );


    //网格线
    pen.setColor(Qt::black);
    pen.setWidth(1);
    p.setPen(pen);

    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++)
//        p.drawRect(50+j*50, 50+i*50, 3, 3);
          p.drawEllipse(QPoint(i*50+50,j*50+50),5,5);
    }




    brush.setStyle(Qt::SolidPattern);

    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            if(table[i][j]==1){
                brush.setColor(Qt::black);
                p.setBrush(brush);
                p.drawEllipse(QPoint(i*50+50,j*50+50),7,7);
            }

//            else if(chessboard[i][j] == 2){
//                brush.setColor(Qt::white);
//                p.setPen(Qt::NoPen);
//                p.setBrush(brush);
//                p.drawEllipse(QPoint( i*50+50, j*50+50 ), 20, 20);
//            }
        }
    }

    for(int i=0;i<_line.size();i++){
        p.drawLine((_line[i].first/10000)*50+50,(_line[i].first%10000)*50+50,(_line[i].second/10000)*50+50,(_line[i].second%10000) *50+50);

        int x1,x2,y1,y2;
        x1=(_line[i].first/10000)*50+50;
        x2=(_line[i].second/10000)*50+50;
        y1=(_line[i].first%10000)*50+50;
        y2=(_line[i].second%10000)*50+50;
        if(x2>=x1&&y2>=y1){
            double tann=((double)abs(y1-y2)/(double)abs(x1-x2));
            double sinn=((double)abs(y1-y2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            double coss=((double)abs(x1-x2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            int placex1,placey1,placex2,placey2;
            placex1=(int)((double)x2-10*coss+10*sinn);
            placey1=(int)((double)y2-10*sinn-10*coss);
            placex2=(int)((double)x2-10*coss);
            placex2=2*placex2-placex1;
            placey2=(int)((double)y2-10*sinn);
            placey2=2*placey2-placey1;
            p.drawLine(placex1,placey1,placex2,placey2);
            p.drawLine(placex1,placey1,x2,y2);
            p.drawLine(x2,y2,placex2,placey2);
        }
        else if(x2<=x1&&y2<=y1){
            double tann=((double)abs(y1-y2)/(double)abs(x1-x2));
            double sinn=((double)abs(y1-y2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            double coss=((double)abs(x1-x2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            int placex1,placey1,placex2,placey2;
            placex1=(int)((double)x2+10*coss-10*sinn);
            placey1=(int)((double)y2+10*sinn+10*coss);
            placex2=(int)((double)x2+10*coss);
            placex2=2*placex2-placex1;
            placey2=(int)((double)y2+10*sinn);
            placey2=2*placey2-placey1;
            p.drawLine(placex1,placey1,placex2,placey2);
            p.drawLine(placex1,placey1,x2,y2);
            p.drawLine(x2,y2,placex2,placey2);
        }
        else if(x2>=x1&&y2<=y1){
            double tann=((double)abs(y1-y2)/(double)abs(x1-x2));
            double sinn=((double)abs(y1-y2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            double coss=((double)abs(x1-x2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            int placex1,placey1,placex2,placey2;
            placex1=(int)((double)x2-10*coss+10*sinn);
            placey1=(int)((double)y2+10*sinn+10*coss);
            placex2=(int)((double)x2-10*coss);
            placex2=2*placex2-placex1;
            placey2=(int)((double)y2+10*sinn);
            placey2=2*placey2-placey1;
            p.drawLine(placex1,placey1,placex2,placey2);
            p.drawLine(placex1,placey1,x2,y2);
            p.drawLine(x2,y2,placex2,placey2);
        }
        else{
            double tann=((double)abs(y1-y2)/(double)abs(x1-x2));
            double sinn=((double)abs(y1-y2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            double coss=((double)abs(x1-x2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            int placex1,placey1,placex2,placey2;
            placex1=(int)((double)x2+10*coss-10*sinn);
            placey1=(int)((double)y2-10*sinn-10*coss);
            placex2=(int)((double)x2+10*coss);
            placex2=2*placex2-placex1;
            placey2=(int)((double)y2-10*sinn);
            placey2=2*placey2-placey1;
            p.drawLine(placex1,placey1,placex2,placey2);
            p.drawLine(placex1,placey1,x2,y2);
            p.drawLine(x2,y2,placex2,placey2);
        }
//        QPainter.drawPolygon(QPoint(x2,y2),QPoint(placex1,placey1),QPoint(placex2,placey2));
    }
    if(type==2&&linestart!=0&&linestart!=moveX*10000+moveY){
        p.drawLine((linestart/10000)*50+50,(linestart%10000)*50+50,moveX*50+50,moveY*50+50);
        int x1,x2,y1,y2;
        x1=(linestart/10000)*50+50;
        x2=moveX*50+50;
        y1=(linestart%10000)*50+50;
        y2=moveY*50+50;
        if(x2>=x1&&y2>=y1){
            double tann=((double)abs(y1-y2)/(double)abs(x1-x2));
            double sinn=((double)abs(y1-y2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            double coss=((double)abs(x1-x2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            int placex1,placey1,placex2,placey2;
            placex1=(int)((double)x2-10*coss+10*sinn);
            placey1=(int)((double)y2-10*sinn-10*coss);
            placex2=(int)((double)x2-10*coss);
            placex2=2*placex2-placex1;
            placey2=(int)((double)y2-10*sinn);
            placey2=2*placey2-placey1;
            p.drawLine(placex1,placey1,placex2,placey2);
            p.drawLine(placex1,placey1,x2,y2);
            p.drawLine(x2,y2,placex2,placey2);
        }
        else if(x2<=x1&&y2<=y1){
            double tann=((double)abs(y1-y2)/(double)abs(x1-x2));
            double sinn=((double)abs(y1-y2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            double coss=((double)abs(x1-x2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            int placex1,placey1,placex2,placey2;
            placex1=(int)((double)x2+10*coss-10*sinn);
            placey1=(int)((double)y2+10*sinn+10*coss);
            placex2=(int)((double)x2+10*coss);
            placex2=2*placex2-placex1;
            placey2=(int)((double)y2+10*sinn);
            placey2=2*placey2-placey1;
            p.drawLine(placex1,placey1,placex2,placey2);
            p.drawLine(placex1,placey1,x2,y2);
            p.drawLine(x2,y2,placex2,placey2);
        }
        else if(x2>=x1&&y2<=y1){
            double tann=((double)abs(y1-y2)/(double)abs(x1-x2));
            double sinn=((double)abs(y1-y2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            double coss=((double)abs(x1-x2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            int placex1,placey1,placex2,placey2;
            placex1=(int)((double)x2-10*coss+10*sinn);
            placey1=(int)((double)y2+10*sinn+10*coss);
            placex2=(int)((double)x2-10*coss);
            placex2=2*placex2-placex1;
            placey2=(int)((double)y2+10*sinn);
            placey2=2*placey2-placey1;
            p.drawLine(placex1,placey1,placex2,placey2);
            p.drawLine(placex1,placey1,x2,y2);
            p.drawLine(x2,y2,placex2,placey2);
        }
        else{
            double tann=((double)abs(y1-y2)/(double)abs(x1-x2));
            double sinn=((double)abs(y1-y2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            double coss=((double)abs(x1-x2)/sqrt((double)(abs((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2)))));
            int placex1,placey1,placex2,placey2;
            placex1=(int)((double)x2+10*coss-10*sinn);
            placey1=(int)((double)y2-10*sinn-10*coss);
            placex2=(int)((double)x2+10*coss);
            placex2=2*placex2-placex1;
            placey2=(int)((double)y2-10*sinn);
            placey2=2*placey2-placey1;
            p.drawLine(placex1,placey1,placex2,placey2);
            p.drawLine(placex1,placey1,x2,y2);
            p.drawLine(x2,y2,placex2,placey2);
        }
    }

    pen.setColor(Qt::red);
    pen.setWidth(1);
    p.setPen(pen);
    p.setBrush(Qt::NoBrush);
    p.drawRect(moveX*50+50-23,moveY*50+50-23,46,46);



    if((moveX>=0&&moveX<=14)&&(moveY>=0&&moveY<=14)&&table[moveX][moveY]==0){
        brush.setColor(QColor(0, 255, 0, 150));
        p.setPen(Qt::NoPen);
        p.setBrush(brush);
        p.drawEllipse(QPoint(moveX*50+50,moveY*50+50),10,10);
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    moveX=(e->x()+25)/50-1;
    moveY=(e->y()+25)/50-1;
    if(isdian==1){
        if(table[moveX][moveY]==1){
            update();
            return;
        }
        if(!((e->x()>=25&&e->x()<=775)&&(e->y()>=25&&e->y()<=775))){
            update();
            return;
        }
        _Moveend=((e->x()+25)/50-1)*10000+(e->y()+25)/50-1;
        for(int i=0;i<placexy.size();i++){
            if(placexy[i]==_Movestart){
                for(int j=0;j<placexy.size();j++){
                    if(graph[((placexy[i]/10000)*15+placexy[i]%10000)][((placexy[j]/10000)*15+placexy[j]%10000)]==1){
                        graph[((placexy[i]/10000)*15+placexy[i]%10000)][((placexy[j]/10000)*15+placexy[j]%10000)]=0;
                        graph[((_Moveend/10000)*15+_Moveend%10000)][((placexy[j]/10000)*15+placexy[j]%10000)]=1;
                    }
                }
                for(int j=0;j<placexy.size();j++){
                    if(graph[((placexy[j]/10000)*15+placexy[j]%10000)][((placexy[i]/10000)*15+placexy[i]%10000)]==1){
                        graph[((placexy[j]/10000)*15+placexy[j]%10000)][((placexy[i]/10000)*15+placexy[i]%10000)]=0;
                        graph[((placexy[j]/10000)*15+placexy[j]%10000)][((_Moveend/10000)*15+_Moveend%10000)]=1;
                    }
                }
                placexy[i]=_Moveend;
                table[moveX][moveY]=1;
                table[_Movestart/10000][_Movestart%10000]=0;
                if(currentX*10000+currentY==_Movestart){
                    currentX=_Moveend/10000;
                    currentY=_Moveend%10000;
                }
                break;
            }
        }
        for(int i=0;i<_line.size();i++){
            if(_line[i].first==_Movestart)
                _line[i].first=_Moveend;
            if(_line[i].second==_Movestart)
                _line[i].second=_Moveend;
        }
        for(int i=0;i<del.size();i++){
            if(del[i]>=100000000&&del[i]-100000000==_Movestart){
                del[i]=_Moveend+100000000;
            }
            else{
                int x=del[i]/300;
                int y=del[i]%300;
                if(((_Movestart/10000+25)/50-1)*10000+(_Movestart%10000+25)/50-1==x)
                    x=((_Moveend/10000+25)/50-1)*10000+(_Moveend%10000+25)/50-1;
                if(((_Movestart/10000+25)/50-1)*10000+(_Movestart%10000+25)/50-1==y)
                    y=((_Moveend/10000+25)/50-1)*10000+(_Moveend%10000+25)/50-1;
            }
        }
    }
    _Movestart=_Moveend;
    update();
}

void MainWindow::mousePressEvent(QMouseEvent* e)
{
    if(table[((e->x()+25)/50-1)][(e->y()+25)/50-1]!=0&&type==1){
        isdian=1;
        _Movestart=((e->x()+25)/50-1)*10000+(e->y()+25)/50-1;
//        memset(table,0,sizeof(table));
    }
    if(type==1){
        printdian(e);
    }
    else if(type==2){
        printxian(e);
    }
//    else if(type==3){
//        _Movestart=((e->x()+25)/50-1)*10000+(e->y()+25)/50-1;
//    }
    update();
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    isdian=0;
    if(type==2){
        if(((e->x()+25)/50-1)*10000+(e->y()+25)/50-1==linestart||table[(e->x()+25)/50-1][(e->y()+25)/50-1]==0||graph[(linestart/10000)*15+linestart%10000][(e->x()+25)/50-1*15+(e->y()+25)/50-1]==1){
            linestart=0;
            update();
            return;
        }
        int x, y;
        if((e->x()>=25&&e->x()<=775)&&(e->y()>=25&&e->y()<=775)&&table[(e->x()+25)/50-1][(e->y()+25)/50-1]==1){
            x=(e->x()+25)/50-1;
            y=(e->y()+25)/50-1;
            _line.push_back(make_pair(linestart,x*10000+y));
            graph[(linestart/10000)*15+linestart%10000][x*15+y]=1;
            del.push_back(((linestart/10000)*15+linestart%10000)*300+x*15+y);
            linestart=0;
        }
    }
    update();
}


void MainWindow::update_table(int x,int y){
    if(!table[x][y]){
        table[x][y]=1;
        currentX=x;
        currentY=y;
        QPoint p(x,y);
        placexy.push_back(x*10000+y);
        del.push_back(100000000+x*10000+y);
        update();
    }
}
void MainWindow::printdian(QMouseEvent *e){
    int x, y;
    if((e->x()>=25&&e->x()<=775)&&(e->y()>=25&&e->y()<=775)&&table[(e->x()+25)/50-1][(e->y()+25)/50-1]==0){
        x=(e->x()+25)/50-1;
        y=(e->y()+25)/50-1;
        update_table(x,y);
    }
}

void MainWindow::printxian(QMouseEvent *e){
    int x, y;
    if((e->x()>=25&&e->x()<=775)&&(e->y()>=25&&e->y()<=775)){
        x=(e->x()+25)/50-1;
        y=(e->y()+25)/50-1;
        if(table[x][y]==0){
            linestart=0;
            return;
        }
        linestart=x*10000+y;
    }
}








MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_inite(){
    ui->radioButton_2->setChecked(true);
    isdian=0;
    type=1;
    currentX=-100;
    currentY=-100;
    moveX=-100;
    moveY=-100;
    memset(table,0,sizeof(table));
    memset(graph,0,sizeof(graph));
    memset(judge,0,sizeof(judge));
    while(!placexy.empty())
        placexy.pop_back();
    while(!_line.empty())
        _line.clear();
    del.clear();
    n=0;
    memset(low,0,sizeof(low));
    memset(dfn,0,sizeof(dfn));
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
    memset(id,0,sizeof(id));
    memset(add,0,sizeof(add));
    vec.clear();
    placexy.clear();
    num_of_tarjan=0;
    num_of_scg=0;
    top=0;
    while(!q.empty())
        q.pop();
    setMouseTracking(true);
}

void MainWindow::addedge(int a,int b){
    edge[top++]={a,b,head[a]};
    head[a]=top-1;
}

void MainWindow::_input(){
    int temp;
    for(int i=0;i<300;i++){
        for(int j=0;j<300;j++){
            if(judge[i]&&judge[j]){
                temp=graph[i][j];
                if(temp==1&&i!=j){
                    m++;
                    addedge(judge[i],judge[j]);
                }
            }
        }
    }
}
void MainWindow::tarjan(int now){
    low[now]=dfn[now]=++num_of_tarjan;
    vec.push_back(now);
    vis[now]=1;
    for(int i=head[now];i!=-1;i=edge[i].next){
        if(!dfn[edge[i].to]){
            tarjan(edge[i].to);
            low[now]=min(low[now],low[edge[i].to]);
        }
        else if(vis[edge[i].to]){
            low[now]=min(low[now],dfn[edge[i].to]);
        }
    }
    if(low[now]==dfn[now]){
        num_of_scg++;
        while(1){
            vis[vec.back()]=0;
            id[vec.back()]=num_of_scg;
            if(vec.back()==now){
                vec.pop_back();
                break;
            }
            vec.pop_back();
        }
    }
}
void MainWindow::suodian(){
    for(int i=1;i<=num_of_scg;i++){
        vvec[i].clear();
    }
    for(int i=0;i<top;i++){
        if(id[edge[i].from]!=id[edge[i].to]){
            vvec[id[edge[i].from]].push_back(id[edge[i].to]);
            add[id[edge[i].to]]++;
        }
    }
}
bool MainWindow::topsort(){
    int num=0,k=0;
    for(int i=1;i<=num_of_scg;i++){
        if(add[i]==0){
            q.push(i);
            num++;
        }
    }
    if(num>1){
        return 0;
    }
    while(!q.empty()){
        int temp=q.front();
        q.pop();
        num=0;
        k++;
        for(int i=0;i<vvec[temp].size();i++){
            int to=vvec[temp][i];
            if(--add[to]==0){
                q.push(to);
                num++;
            }
        }
    }
    return k=num_of_scg;
}


void MainWindow::on_pushButton_3_clicked()
{
    if(!del.empty()){
        int num=del.back();
        del.pop_back();
        if(num>=100000000){
            int x,y;
            x=(num-100000000)/10000;
            y=(num-100000000)%10000;
            table[x][y]=0;
            placexy.pop_back();
        }
        else{
            int start=num/300;
            int end=num%300;
            graph[start][end]=0;
            _line.pop_back();
        }
    }
    update();
}

void MainWindow::on_radioButton_2_clicked()
{
    type=1;
}

void MainWindow::on_radioButton_clicked()
{
    type=2;
}

void MainWindow::on_pushButton_2_clicked()
{

//    memset(head,-1,sizeof(head));
    QString ans;
    int num_of_flowin=0;
    int num_of_flowout=0;
    for(int i=0;i<placexy.size();i++){
        int flag=0;
        for(int j=0;j<placexy.size();j++){
            if(graph[(placexy[i]/10000)*15+placexy[i]%10000][(placexy[j]/10000)*15+placexy[j]%10000]==1){
                flag=1;
                break;
            }
        }
        if(flag==0){
            num_of_flowin++;
        }
        flag=0;
        for(int j=0;j<placexy.size();j++){
            if(graph[(placexy[j]/10000)*15+placexy[j]%10000][(placexy[i]/10000)*15+placexy[i]%10000]==1){
                flag=1;
                break;
            }
        }
        if(flag==0){
            num_of_flowout++;
        }
    }
    if(num_of_flowin>=2||num_of_flowout>=2){
        ans=QString::fromStdString("弱连通图");
        ui->textEdit->setText(ans);
        _inite();
        update();
        return;
    }

    for(int i=0;i<260;i++){
       for(int j=0;j<260;j++){
            if(graph[i][j]==1||graph[j][i]==1){
                n++;
                judge[i]=n;
                break;
            }
        }
    }
    _input();
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i);
    }
    if(num_of_scg==1){
        ans=QString::fromStdString("强连通图");
        ui->textEdit->setText(ans);
        _inite();
        update();
        return;
    }
    suodian();
    if(topsort()==0)//拓扑排序
        ans=QString::fromStdString("弱连通");
    else
        ans=QString::fromStdString("单向连通");
    ui->textEdit->setText(ans);
    _inite();
    update();
}

//void MainWindow::on_radioButton_3_clicked()
//{
//    type=3;
//}
