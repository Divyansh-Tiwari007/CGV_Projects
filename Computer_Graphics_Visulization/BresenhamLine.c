#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

int xstart,xend,ystart,yend;
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
}

void setPixel(int x,int y)
{
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
    glFlush();
}

void Bresenhamline()
{
    int p,x,y;
    
    if(xstart>xend)
    {
        x=xend;
        y=yend;
        xend=xstart;
        yend=ystart;
    }
    else
    {
        x=xstart;
        y=ystart;
    }

    int dx=abs(xend-x), dy=abs(yend-y);
    int twodx=2*dx, twody=2*dy, twodxminustwody=2*(dx-dy), twodyminustwodx=2*(dy-dx);

    glColor3f(1,0,0);
    glPointSize(2);

    if(dx>dy) //m < 1
    {
        p=2*dy-dx;
        setPixel(x,y);
        while(x<xend)
        {
            x+=1;
            if(p<0)
                p+=twody;
            else
            {
                y+=1;
                p+=twodyminustwodx;
            }
            setPixel(x,y);
        }
    }
    else  //m > 1
    {
        p=2*dy-dx;
        setPixel(x,y);
        while(y<yend)
        {
            y+=1;
            if(p<0)
                p+=twodx;
            else
            {
                x+=1;
                p+=twodxminustwody;
            }
            setPixel(x,y);
        }
    }
    
}

void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(300,300,100,100);
    Bresenhamline();
    glFlush();
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB| GLUT_SINGLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bresenham's Line");
    myinit();
    printf("Enter Co-ordinates of first point : ");
    scanf("%d %d",&xstart, &ystart);
    printf("Enter Co-ordinates of second point : ");
    scanf("%d %d",&xend, &yend);
    glutDisplayFunc(display);
    glutMainLoop();
}