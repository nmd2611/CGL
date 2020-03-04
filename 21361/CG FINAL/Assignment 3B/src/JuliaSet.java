import java.applet.*;
import java.awt.*;
import java.awt.image.*;
/*
<applet code="JuliaSet.class" width="400" height="450"></applet>
*/
public class JuliaSet extends Applet {
    
 Label num1Label = new Label("Real:");
 Label num2Label = new Label("Imaginary:");
 TextField num1 = new TextField("-0.74");
 TextField num2 = new TextField("0.11");
 String input1 = "";
 String input2 = "";
 Button submit = new Button("Submit");

 double realinput;
 double imaginput;
 
 double realpart; 
 double imagpart; 
 double realinc; 
 double imaginc; 
 double realjuliaconst; 
 double imagjuliaconst; 
 double storerealpart; 
 double storeimagpart;
 double a;
 double b;
 double btemp;
 boolean diverge;
 int i;
 

 public void init() {

  add(num1Label);
  add(num1);
  add(num2Label);
  add(num2);
  add(submit);

  realjuliaconst = -0.74;
  imagjuliaconst = 0.11;

  setBackground(Color.black);
   
 } // end init

 public boolean action(Event evt, Object arg) {

   if (evt.target instanceof Button) {

        String label = (String)arg;
                  
		  if (label.equals("Submit")) {
                
                       input1=num1.getText();
                       input2=num2.getText();
                       
                       realinput = Double.parseDouble(input1);
                       imaginput = Double.parseDouble(input2);

                       realjuliaconst = realinput;
                       imagjuliaconst = imaginput;

                       repaint();

                  } return true;
                       
    } else return false;


 } 
 public void paint(Graphics g) {
 

  realpart = -2;
  imagpart = 2;
  realinc = 0.01;
  imaginc = 0.01;
 
  g.setColor(Color.white);
  g.drawString(realjuliaconst+" + "+imagjuliaconst+"i",160,42);
 
   realpart = realpart - realinc; // this is done once so realpart is at boundary on 1st pass
   
     for (int x = 0 ; x < 400; x++) {

     realpart = realpart + realinc;
     imagpart = 2.01;  // reset to top of window

     for (int y = 50 ; y < 450; y++) {

       imagpart = imagpart - imaginc;
 
       storerealpart = realpart; // store current location in complex plane
       storeimagpart = imagpart;
       
       a = realpart; b = imagpart; i = 0; diverge = false; // a and b are the current point
 
         while (i < 100) {
           btemp = 2*a*b; // store this product otherwise it would also effect value of a
           a = a*a - b*b + realjuliaconst;
           b = btemp + imagjuliaconst;
           if ( (a*a + b*b) > 4 ) {diverge=true; break;} 
           i++;
         }

       if (diverge==true) {
				if (i<20) g.setColor(Color.orange);
                                if (i>19 && i<40) g.setColor(Color.red);
                                if (i>39 && i<60) g.setColor(Color.blue);
                                if (i>59 && i<80) g.setColor(Color.yellow);
                                if (i>79) g.setColor(Color.white);
				g.drawRect(x, y, 0, 0);
                           } 
      realpart = storerealpart; // restore value of current point
      imagpart = storeimagpart;

     } // end y loop

   } // end x loop
   g.setColor(Color.black);
   g.drawLine(200,50,200,450);
   g.drawLine(0,250,400,250);
   g.drawOval(0,50,400,400);
   g.drawOval(100,150,200,200);

 } // end paint routine
 
}
