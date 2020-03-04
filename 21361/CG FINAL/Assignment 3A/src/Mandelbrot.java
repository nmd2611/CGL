import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;

public class Mandelbrot {
    public static void main(String[] args) throws Exception {
        int width = 1920, height = 1080, max = 1000;
        BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
        int black = 0x00FFFF, white = 0xFFFFFF;

        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                double c_re = (col - width/2)*4.0/width;
                double c_im = (row - height/2)*4.0/width;
                double x = 0, y = 0;
                int iterations = 0;
                while (x*x+y*y < 4 && iterations < max) {
                    double x_new = x*x-y*y+c_re;
                    y = 2*x*y+c_im;
                    x = x_new;
                    iterations++;
                } 
                if (iterations < max) image.setRGB(col, row, white);
                else image.setRGB(col, row, black);
            }
        }

        ImageIO.write(image, "png", new File("vnk.png"));
    }
}
