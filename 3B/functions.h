#include <image.h>

void ReadImage(char *filename, Image &output);
void WriteImage(char *filename, Image &img);

void HalfSize(Image &input, Image &output);
void LeftRightCombine(Image &leftInput, Image &rightinput, Image &output);
void TopBottomCombine(Image &topInput, Image &bottomInput, Image &output);
void Blend(Image &input1, Image &input2, double factor, Image &output);
