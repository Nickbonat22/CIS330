#include <image.h>
#include <functions.h>

int main(int argc, char *argv[])
{
    Image img, img2, img3, img4, img5, img6, img7, img8;

    ReadImage(argv[1], img);
    HalfSize(img, img2);
    LeftRightCombine(img2, img2, img3);
    TopBottomCombine(img3, img3, img4);
    HalfSize(img4, img5);
    LeftRightCombine(img5, img2, img6);
    TopBottomCombine(img6, img3, img7);
    Blend(img7, img, 0.795, img8);
    WriteImage(argv[2], img8);
}
