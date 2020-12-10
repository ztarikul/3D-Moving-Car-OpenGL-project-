
#include <windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include<GL/glut.h>

#define pi (2*acos(0.0))

#define sqrt2 (sqrt(2))

typedef struct point
{
	double x,y,z;
}Point;

bool drawAxes = true;
bool drawRoad = false;
bool drawGrid = false;
bool lightOn = true;
int leftKey=0;
float tyreAngle = 0;
float lightBoxAngle =0;

float quadAngle = 0;
float boxAngle = 0;
float boxScaleFactor_x = 1 , boxScaleFactor_y = 1 , boxScaleFactor_z = 1;
float tyreScaleFactor_x = 1 , tyreScaleFactor_y = 1, tyreScaleFactor_z = 1;
float tinyBoxAngle = 0;
float background = 0;
//my code starts
float pos_x=500,pos_y=300,pos_z=200;
float front_tyre_x=150, back_tyre_x=-150, box_x=0;
//my code ends

Point pos, u, r, l;

void displayAxes()
{
	if(drawAxes)
	{
		glBegin(GL_LINES);
		{
		    glColor3f(1.0, 0, 0);

			glVertex3f( 500,0,0); // a point on pos x axis
			glVertex3f(-500,0,0); // a point on neg x axis

			glColor3f(0, 1.0, 0);

			glVertex3f(0,-500,0); // a point on pos y axis
			glVertex3f(0, 500,0); // a point on neg y axis

			glColor3f(0, 0, 1.0);

			glVertex3f(0,0, 500);  // a point on pos z axis
			glVertex3f(0,0,-500);   // a point on neg z axis
		}
		glEnd();
	}
}

Point func(Point vect, Point perp, int dir)
{
    double c = cos(pi/180);
    double s = dir * sin(pi/180);
    Point point;
    point.x = c * vect.x + s * perp.x;
    point.y = c * vect.y + s * perp.y;
    point.z = c * vect.z + s * perp.z;
    c = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
    point.x /= c;
    point.y /= c;
    point.z /= c;
    return point;
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){
		case '1': {
            Point l1 = func(l, r, -1);
            r = func(r, l, 1);
            l = l1;
            break;
		}
		case '2': {
            Point l1 = func(l, r, 1);
            r = func(r, l, -1);
            l = l1;
            break;
		}

		case '3': {
            Point u1 = func(u, l, -1);
            l = func(l, u, 1);
            u = u1;
            break;
        }
        case '4': {
            Point u1 = func(u, l, 1);
            l = func(l, u, -1);
            u = u1;
            break;
        }
        case '5': {
            Point r1 = func(r, u, -1);
            u = func(u, r, 1);
            r = r1;
            break;
        }
        case '6':{
            Point r1 = func(r, u, 1);
            u = func(u, r, -1);
            r = r1;
            break;
        }
        case '7':{

            tyreAngle += 5;
            front_tyre_x +=5;
            back_tyre_x +=5;
            box_x +=5;
            break;
        }
        case '8':{

            tyreAngle -= 5;
            front_tyre_x -=5;
            back_tyre_x -=5;
            box_x -=5;
		        break;
        }

        case '9':{

            lightBoxAngle += 5;
		        break;
        }

        case '0':{

            lightBoxAngle -= 5;
		        break;
        }

        case 'a':{

                boxScaleFactor_x += 0.2;
		        tyreScaleFactor_x +=0.2;
		        break;
        }

        case 'A':{

                boxScaleFactor_x += 0.2;
		        tyreScaleFactor_x +=0.2;
		        break;
        }

        case 'b':{

                boxScaleFactor_x -= 0.2;
		        tyreScaleFactor_x -=0.2;
		        break;
        }

        case 'B':{

                boxScaleFactor_x -= 0.2;
		        tyreScaleFactor_x -=0.2;
		        break;
        }

        case 'c':{

                boxScaleFactor_y += 0.2;
		        tyreScaleFactor_y +=0.2;
		        break;
        }

        case 'C':{

                boxScaleFactor_y += 0.2;
		        tyreScaleFactor_y +=0.2;
		        break;
        }

        case 'd':{

                boxScaleFactor_y -= 0.2;
		        tyreScaleFactor_y -=0.2;
		        break;
        }

        case 'D':{

                boxScaleFactor_y -= 0.2;
		        tyreScaleFactor_y -=0.2;
		        break;
        }

        case 'e':{

                boxScaleFactor_z += 0.2;
		        tyreScaleFactor_z +=0.2;
		        break;
        }

        case 'E':{

                boxScaleFactor_z += 0.2;
		        tyreScaleFactor_z +=0.2;
		        break;
        }

        case 'f':{

                boxScaleFactor_z -= 0.2;
		        tyreScaleFactor_z -=0.2;
		        break;
        }

         case 'F':{

                boxScaleFactor_z -= 0.2;
		        tyreScaleFactor_z -=0.2;
		        break;
        }
		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN: // down arrow
		    {
		        //my code starts
		        double d= 1/ sqrt2;
		        pos_x=pos_x-((-d)*3);
		        pos_y=pos_y-((-d)*3);
		        pos_z=pos_z-(0*3);
		        pos ={pos_x,pos_y,pos_z};
		        break;
		        //my code ends


		        /*
		        quadAngle += 5;
		        printf("Quad Angle %f\n", quadAngle);
		        break;
		        */
		    }

		case GLUT_KEY_UP:   // up arrow
		    {
		        //my code starts
		        double d= 1/ sqrt2;
		        pos_x=pos_x+((-d)*3);
		        pos_y=pos_y+((-d)*3);
		        pos_z=pos_z+(0*3);
		        pos ={pos_x,pos_y,pos_z};
		        break;
		        //my code ends

		        /*
		        quadAngle -= 5;
		        printf("Quad Angle %f\n", quadAngle);
		        break;
		        */
		    }

		case GLUT_KEY_RIGHT:    // right arrow
		    {
		        //my code starts
		        double d= 1/ sqrt2;
		        pos_x=pos_x+((-d)*3);
		        pos_y=pos_y+((d)*3);
		        pos_z=pos_z+(0*3);
		        pos ={pos_x,pos_y,pos_z};
		        break;
		        //my code ends

		        /*
		        boxAngle += 5;
		        printf("Box Angle %f\n", boxAngle);
		        break;
		        */
		    }

		case GLUT_KEY_LEFT:     // left arrow
		    {
		        //my code starts
		        double d= 1/ sqrt2;
		        pos_x=pos_x-((-d)*3);
		        pos_y=pos_y-((d)*3);
		        pos_z=pos_z-(0*3);
		        pos ={pos_x,pos_y,pos_z};
		        break;
		        //my code ends

		        /*
		        boxAngle -= 5;
		        printf("Box Angle %f\n", boxAngle);
		        break;
		        */
		    }

		case GLUT_KEY_PAGE_UP:
		    {
		        //my code starts
		        double d= 1/ sqrt2;
		        pos_x=pos_x+(0*3);
		        pos_y=pos_y+(0*3);
		        pos_z=pos_z+(1*3);
		        pos ={pos_x,pos_y,pos_z};
		        break;
		        //my code end

		        /*
                boxScaleFactor += 0.2;
                break;
                */
		    }

		case GLUT_KEY_PAGE_DOWN:
		    {
		        //my code starts
		        double d= 1/ sqrt2;
		        pos_x=pos_x-(0*3);
		        pos_y=pos_y-(0*3);
		        pos_z=pos_z-(1*3);
		        pos ={pos_x,pos_y,pos_z};
		        break;
		        //my code ends
		        /*
		        boxScaleFactor -= 0.2;
                break;
                */
		    }

		case GLUT_KEY_HOME:
		    {

		        boxScaleFactor_x += 0.2;
		        boxScaleFactor_y += 0.2;
		        boxScaleFactor_z += 0.2;
		        tyreScaleFactor_x +=0.2;
		        tyreScaleFactor_y +=0.2;
		        tyreScaleFactor_z +=0.2;
                break;
                /*
		        tyreAngle += 5;
		        break;
		        */
		    }

        case GLUT_KEY_END:
            {

                boxScaleFactor_x -= 0.2;
		        boxScaleFactor_y -= 0.2;
		        boxScaleFactor_z -= 0.2;
		        tyreScaleFactor_x -=0.2;
		        tyreScaleFactor_y -=0.2;
		        tyreScaleFactor_z -=0.2;
                break;
                /*
                tyreAngle -= 5;
                break;
                */
            }

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN) // 2 times?? in ONE click? -- solution is checking DOWN or UP
            {

			}
			else if(state == GLUT_UP)
            {
                if(leftKey%2==0)
                {
                    drawAxes=false;

                }

                else
                {
                    drawAxes=true;


                }
                leftKey++;
            }
            break;
		default:
			break;
	}
}

void displayTyre(float tyreRadius, float tyreWidth)
{
    int tyreSlices = 36;
    float sliceWidth = (2 * M_PI * tyreRadius) / tyreSlices;
    float sliceAngle = 360 / tyreSlices;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);
        glVertex3f(tyreRadius, halfTyreWidth, 0);
        glVertex3f(-tyreRadius,halfTyreWidth, 0);

        glColor3f(1, 1, 1);
        glVertex3f(-tyreRadius, -halfTyreWidth, 0);
        glVertex3f(tyreRadius, -halfTyreWidth, 0);

    }
    glEnd();


    glBegin(GL_QUADS);
    {
        glColor3f(1, 1, 1);
        glVertex3f(0,halfTyreWidth, tyreRadius);
        glVertex3f(0,halfTyreWidth, -tyreRadius);
        glColor3f(1, 0, 0);
        glVertex3f(0,-halfTyreWidth,  -tyreRadius);
        glVertex3f(0,-halfTyreWidth, tyreRadius);
    }
    glEnd();



    for(int i=0; i<tyreSlices; i++)
    {
        //line added by me starts
        if(i%2==0)
        {
            glColor3f(1, 1, 1);

        }

        else
        {
            glColor3f(1, 0, 0);
        }
        //line added by me ends

        glPushMatrix();
        glRotatef(sliceAngle*i, 0, 1, 0);
        glTranslatef( tyreRadius,0, 0);
        glBegin(GL_QUADS);
        {
            glVertex3f(0,halfTyreWidth,  halfSliceWidth);
            glVertex3f(0,halfTyreWidth,  -halfSliceWidth);
            glVertex3f(0,-halfTyreWidth,  -halfSliceWidth);
            glVertex3f(0,-halfTyreWidth, halfSliceWidth);
        }
        glEnd();
        glPopMatrix();
    }
}

void displayGrid()
{
	if(drawGrid)
	{
		glBegin(GL_LINES);
		{

		    glColor3f(1, 0, 0);

			glVertex3f( 450,0,0); // a point on pos x axis
			glVertex3f(-450,0,0); // a point on neg x axis

             glColor3f(1, 0, 0);

			glVertex3f( 450,50,0);
			glVertex3f(-450,50,0);

			 glColor3f(1, 0, 0);

			glVertex3f( 450,-50,0);
			glVertex3f(-450,-50,0);

			glColor3f(1, 0, 0);

			glVertex3f( 450,100,0);
			glVertex3f(-450,100,0);
			glColor3f(1, 0, 0);

			glVertex3f( 450,-100,0);
			glVertex3f(-450,1-00,0);

			glColor3f(1, 0, 0);

			glVertex3f( 450,150,0);
			glVertex3f(-450,150,0);

			glColor3f(1, 0, 0);

			glVertex3f( 450,-150,0);
			glVertex3f(-450,-150,0);

			glColor3f(1, 0, 0);

			glVertex3f( 450,200,0);
			glVertex3f(-450,200,0);

			glColor3f(1, 0, 0);

			glVertex3f( 450,-200,0);
			glVertex3f(-450,-200,0);

            glColor3f(0, 1, 0);

			glVertex3f(0,-450,0);
			glVertex3f(0, 450,0);

			glColor3f(0, 1, 0);

			glVertex3f(50,-450,0);
			glVertex3f(50, 450,0);

			glColor3f(0, 1, 0);

			glVertex3f(-50,-450,0);
			glVertex3f(-50, 450,0);

			glColor3f(0, 1, 0);

			glVertex3f(100,-450,0);
			glVertex3f(00, 450,0);

			glColor3f(0, 1, 0);

			glVertex3f(-100,-450,0);
			glVertex3f(-100, 450,0);

            glColor3f(0, 1, 0);
            glVertex3f(150,-450,0);
			glVertex3f(150, 450,0);

			glColor3f(0, 1.0, 0);
            glVertex3f(-150,-450,0);
			glVertex3f(-150, 450,0);


			glColor3f(0, 1.0, 0);
            glVertex3f(200,-450,0);
			glVertex3f(200, 450,0);

			glColor3f(0, 1.0, 0);
            glVertex3f(-200,-450,0); // a point on pos y axis
			glVertex3f(-200, 450,0);

			glColor3f(0, 1.0, 0);
            glVertex3f(250,-450,0);
			glVertex3f(250, 450,0);

			glColor3f(0, 1.0, 0);
            glVertex3f(-250,-450,0); // a point on pos y axis
			glVertex3f(-250, 450,0);

			glColor3f(0, 1.0, 0);
            glVertex3f(300,-450,0); // a point on pos y axis
			glVertex3f(300, 450,0);


		}
		glEnd();
	}
}


void displayRoad() // width along x axis, length along z axis
{
    if(drawRoad)
    {

    glBegin(GL_QUADS);
    {
           glColor3f(0.72, .7, .69);
           glVertex3f(550,-200,0);
           glVertex3f(-550, -200,0);
           glVertex3f(-550,200,0);
           glVertex3f(550, 200,0);
           glColor3f(1, 1,1);
           glVertex3f(550,-210,0);
           glVertex3f(-550,-210,0);
           glVertex3f(-550,210,0);
           glVertex3f(550, 210,0);


    }
    glEnd();

    }
}

void displayBIGBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 9;


    glBegin(GL_QUADS);
    {
        glColor3f(1, 0.6, 0);//front and back surface of car

        glVertex3f(halfBoxWidth*5,halfBoxLength, halfBoxHeight);
        glVertex3f( halfBoxWidth*5,-halfBoxLength, halfBoxHeight);
        glVertex3f( halfBoxWidth*5,-halfBoxLength, -halfBoxHeight);
        glVertex3f( halfBoxWidth*5,halfBoxLength, -halfBoxHeight);

        glVertex3f( -halfBoxWidth*5,halfBoxLength, halfBoxHeight);
        glVertex3f( -halfBoxWidth*5, -halfBoxLength, halfBoxHeight);
        glVertex3f( -halfBoxWidth*5, -halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,halfBoxLength, -halfBoxHeight);


        glColor3f(0.8, 0.8, 0);//side surface of car

        glVertex3f( halfBoxWidth*5,halfBoxLength, halfBoxHeight);
        glVertex3f( halfBoxWidth*5,halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*5, halfBoxLength, halfBoxHeight);

        glVertex3f( halfBoxWidth*5,-halfBoxLength, halfBoxHeight);
        glVertex3f( halfBoxWidth*5,-halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,-halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,-halfBoxLength, halfBoxHeight);

        glColor3f(0.6, 0.4, 0);//upper and lower surface of car

        glVertex3f( halfBoxWidth*5,halfBoxLength, halfBoxHeight);
        glVertex3f( halfBoxWidth*5,-halfBoxLength, halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,-halfBoxLength, halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,halfBoxLength, halfBoxHeight);

        glVertex3f( halfBoxWidth*5,halfBoxLength, -halfBoxHeight);
        glVertex3f( halfBoxWidth*5,-halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,-halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,halfBoxLength, -halfBoxHeight);
    }
    glEnd();
}

void displaySMALLBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength /1.5, halfBoxWidth = boxWidth /2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0.8, 0.4);//front side of car
        glVertex3f( halfBoxWidth*3,halfBoxLength, halfBoxHeight);
        glColor3f(1, 1, 0.8);
        glVertex3f( halfBoxWidth*3,-halfBoxLength, halfBoxHeight);
        glColor3f(1, 0.8, 0.4);
        glVertex3f( halfBoxWidth*5,-halfBoxLength, -halfBoxHeight);
        glColor3f(1, 1, 0.8);
        glVertex3f( halfBoxWidth*5,halfBoxLength, -halfBoxHeight);

        glColor3f(1, 0.8, 0.4);//back side of car
        glVertex3f( -halfBoxWidth*3,halfBoxLength, halfBoxHeight);
        glVertex3f( -halfBoxWidth*3,-halfBoxLength, halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,-halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,halfBoxLength, -halfBoxHeight);


        glColor3f(0.988, 0.564, 0.011);// sides of car

        glVertex3f( halfBoxWidth*3,halfBoxLength, halfBoxHeight);
        glVertex3f( halfBoxWidth*5,halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*3,halfBoxLength, halfBoxHeight);


        glVertex3f( halfBoxWidth*3,-halfBoxLength, halfBoxHeight);
        glVertex3f( halfBoxWidth*5,-halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,-halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*3,-halfBoxLength, halfBoxHeight);

        glColor3f(0.4, 0.2, 0);//up side and down side of car

        glVertex3f( halfBoxWidth*3,halfBoxLength, halfBoxHeight);
        glVertex3f( halfBoxWidth*3,-halfBoxLength, halfBoxHeight);
        glVertex3f( -halfBoxWidth*3,-halfBoxLength, halfBoxHeight);
        glVertex3f( -halfBoxWidth*3,halfBoxLength, halfBoxHeight);


        glVertex3f( halfBoxWidth*5,halfBoxLength, -halfBoxHeight);
        glVertex3f( halfBoxWidth*5,-halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,-halfBoxLength, -halfBoxHeight);
        glVertex3f( -halfBoxWidth*5,halfBoxLength, -halfBoxHeight);
    }
    glEnd();
}

void displayLIGHTSTAND(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.6, 0.4, 0.2);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);


        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.8, 0.2, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

    }
    glEnd();
}

void displayLIGHTBOX(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {

        glColor3f(1, 0, 0);//front part of the light box

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(1, 1, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);



        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
/*

void displayHeadlight(float HeadlightLength,float HeadlightWidth,float HeadlightHeight )
{
    float halfLength = HeadlightLength / 2, halfWidth = HeadlightWidth / 2, halfHeight = HeadlightHeight / 2;


    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);//front and back surface of car

        glVertex3f(0,halfLength, halfHeight);
        glVertex3f( 0,-halfLength, halfHeight);
        glVertex3f(0,-halfLength, -halfHeight);
        glVertex3f( 0,halfLength, -halfHeight);


    }
    glEnd();

}
*/

void displayLight(float lightLength, float lightWidth, float lightHeight,float lightboxHeight, float lightstandHeight)
{
    if(lightOn)
    {
        //float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    float halfLightLength = lightLength / 2, halfLightWidth = lightWidth / 2, halfLightHeight = lightHeight / 2;

    glTranslatef(350,-15,((lightboxHeight/6) + (lightstandHeight/6)));
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);//front part of the light box

        glVertex3f(  halfLightLength,0,halfLightHeight);
        glVertex3f(  halfLightLength,0,-halfLightHeight);
        glVertex3f(  -halfLightLength,0,-halfLightHeight);
        glVertex3f( -halfLightLength,0,halfLightHeight);

    }
    glEnd();

    glTranslatef(0,30,0);
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);//front part of the light box

        glVertex3f(  halfLightLength,0,halfLightHeight);
        glVertex3f(  halfLightLength,0,-halfLightHeight);
        glVertex3f(  -halfLightLength,0,-halfLightHeight);
        glVertex3f( -halfLightLength,0,halfLightHeight);

    }
    glEnd();



    glTranslatef(0,-32,-((lightboxHeight/6) + (lightstandHeight/6)));
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);//front part of the light box

        glVertex3f(  halfLightLength,-30,halfLightHeight);
        glVertex3f(  halfLightLength,-30,-halfLightHeight);
        glVertex3f(  -halfLightLength,0,-halfLightHeight);
        glVertex3f( -halfLightLength,0,halfLightHeight);

    }
    glEnd();

    glTranslatef(0,37,0);
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);//front part of the light box

        glVertex3f(  halfLightLength,-30,halfLightHeight);
        glVertex3f(  halfLightLength,-30,-halfLightHeight);
        glVertex3f(  -halfLightLength,0,-halfLightHeight);
        glVertex3f( -halfLightLength,0,halfLightHeight);

    }
    glEnd();

    glTranslatef(0,-40,-((lightboxHeight/6) + (lightstandHeight/6)));
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);//front part of the light box

        glVertex3f(  halfLightLength,-30,halfLightHeight);
        glVertex3f(  halfLightLength,-30,-halfLightHeight);
        glVertex3f(  -halfLightLength,0,-halfLightHeight);
        glVertex3f( -halfLightLength,0,halfLightHeight);

    }
    glEnd();

    glTranslatef(0,45,0);
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);//front part of the light box

        glVertex3f(  halfLightLength,-30,halfLightHeight);
        glVertex3f(  halfLightLength,-30,-halfLightHeight);
        glVertex3f(  -halfLightLength,0,-halfLightHeight);
        glVertex3f( -halfLightLength,0,halfLightHeight);

    }
    glEnd();

    }



}


void displayScene()
{
    //Primitive Object dimensions

    float quadLength = 100, quadWidth = 60;
    float largeBoxLength = 160, largeBoxWidth = 100, largeBoxHeight = 100;
    float smallBoxLength = 120, smallBoxWidth = 70, smallBoxHeight = 50;
    float HeadlightLength = 50, HeadlightWidth = 50, HeadlightHeight = 50;
    float tyreRadius = 30, tyreWidth = 10;
    float lightstandLength = 20, lightstandWidth = 20, lightstandHeight = 70;
    float lightboxLength = 40, lightboxWidth = 40, lightboxHeight = 40;
    float lightLength=700, lightWidth=10, lightHeight=10;


   /** Principal Axes **/

    displayAxes();
    displayGrid();
    displayRoad();

/** Car Tyres **/

//front right tyre
    glPushMatrix();
    glTranslatef(front_tyre_x*boxScaleFactor_x, 70*boxScaleFactor_y,50); // places the tyre
    glRotatef(tyreAngle, 0, 1, 0); // check what happens to the tyre after exchanging the order of translation and rotation
    glScalef(tyreScaleFactor_x, tyreScaleFactor_y, tyreScaleFactor_z);
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();

 //back right tyre
    glPushMatrix();
    glTranslatef(back_tyre_x*boxScaleFactor_x, 70*boxScaleFactor_y, 50); // places the tyre on top of both boxes
    glRotatef(tyreAngle, 0, 1, 0); // check what happens to the tyre after exchanging the order of translation and rotation
    glScalef(tyreScaleFactor_x, tyreScaleFactor_y, tyreScaleFactor_z);
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();



    //front left tyre
    glPushMatrix();
    glTranslatef(front_tyre_x*boxScaleFactor_x, -70*boxScaleFactor_y, 50); // places the tyre on top of both boxes
    glRotatef(tyreAngle, 0, 1, 0); // check what happens to the tyre after exchanging the order of translation and rotation
    glScalef(tyreScaleFactor_x, tyreScaleFactor_y, tyreScaleFactor_z);
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();

 //back left tyre
    glPushMatrix();
    glTranslatef(back_tyre_x*boxScaleFactor_x, -70*boxScaleFactor_y, 50); // places the tyre on top of both boxes
    glRotatef(tyreAngle, 0, 1, 0); // check what happens to the tyre after exchanging the order of translation and rotation
    glScalef(tyreScaleFactor_x, tyreScaleFactor_y, tyreScaleFactor_z);
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();


    /** Car Body **/

    glPushMatrix();
    glTranslatef(boxScaleFactor_x*box_x, 0, tyreScaleFactor_z*tyreRadius+60);
    glScalef(boxScaleFactor_x, boxScaleFactor_y, boxScaleFactor_z);
    displayBIGBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box

    //glTranslatef(boxScaleFactor_x*box_x, -boxScaleFactor_y*20, tyreScaleFactor_z*tyreRadius+60);
    //displayHeadlight(HeadlightLength,HeadlightWidth,HeadlightHeight);

    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/8)); // places the small box on top of the large box
    displaySMALLBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box




    /**** LIGHT STAND and LIGHT BOX ****/
    glTranslatef(0, 0, ((smallBoxHeight/5) + (largeBoxHeight/5)+(lightboxHeight/2) ));//placement of light Stand
    displayLIGHTSTAND(lightstandLength, lightstandWidth, lightstandHeight);

    glTranslatef(0, 0, ((lightboxHeight/2) + (lightstandHeight/2)));//placement of LightBox
    glRotatef(lightBoxAngle, 0, 0, 1);
    displayLIGHTBOX(lightboxLength, lightboxWidth, lightboxHeight);

    /*** LIGHT ON ***/


    displayLight(lightLength, lightWidth,lightHeight,lightboxHeight,lightstandHeight);

    glPopMatrix();




}

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(background, background, background,0);	//sets background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // sets the current matrix to identity
    gluLookAt(pos.x, pos.y, pos.z, pos.x+l.x, pos.y+l.y, pos.z+l.z, u.x, u.y, u.z); // sets camera position and direction

    displayScene();

	glutSwapBuffers();
}



void animate(){
    tinyBoxAngle += 0.05;
	glutPostRedisplay();
}

void init(){
    glClearColor(background, background, background,0); 	//sets background color

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity(); // sets the current matrix to identity
    gluPerspective(80,	1,	1,	1000.0);

	// to understand the following values, read the specification pdf
    double d = 1 / sqrt2;
    pos = {pos_x, pos_y, pos_z};
    u = {0, 0, 1};
    r = {-d, d, 0};
    l = {-d, -d, 0};
}

void subMenu(int id)
{
    if(id == 3)
    {
        background = 1;
    }
    else if(id == 4)
    {
        background = 0;
    }

}
void RoadsubMenu(int id)
{
    if(id == 5)
    {
        drawRoad = true;
    }
    else if(id == 6)
    {
        drawRoad = false;
    }
}

void LightsubMenu(int id)
{
    if(id == 9)
    {
        lightOn = true;
    }
    else if(id == 10)
    {
        lightOn = false;
    }
}




void mainMenu(int id)
{
    if(id == 1)
    {
        drawAxes = true;
    }
    else if(id == 2)
    {
        drawAxes = false;

    }
    if(id == 7)
    {
         drawGrid= true;
    }
    else if(id == 8)
    {
        drawGrid = false;

    }

}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	int subMenuNo = glutCreateMenu(subMenu);
    glutAddMenuEntry("White", 3);
	glutAddMenuEntry("Black", 4);
	int RoadsubMenuNo = glutCreateMenu(RoadsubMenu);
	glutAddMenuEntry("SHOW ROAD", 5);
	glutAddMenuEntry("HIDE ROAD", 6);

	int LightsubMenuNo = glutCreateMenu(LightsubMenu);
	glutAddMenuEntry("Light On", 9);
	glutAddMenuEntry("Light Off", 10);

    glutCreateMenu(mainMenu);
	glutAddMenuEntry("Axes On", 1);
	glutAddMenuEntry("Axes Off", 2);
	glutAddMenuEntry("Grid On", 7);
	glutAddMenuEntry("Grid Off", 8);

	glutAddSubMenu("Road", RoadsubMenuNo);
	glutAddSubMenu("Light", LightsubMenuNo);
	glutAddSubMenu("Background", subMenuNo);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();		//The main loop of OpenGL, this function never returns

	return 0;
}
