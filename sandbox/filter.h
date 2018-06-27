#include <source.h>
#include <sink.h>

class Filter : public Source, public Sink
{
	public:
		virtual void Update();
		virtual const char *SourceName();
		virtual const char *SinkName();
		virtual const char *FilterName() = 0;
};

class Shrinker : public Filter
{
	public:
		void Execute();
		virtual const char *FilterName(){return "Shrinker";}
};

class LRCombine : public Filter
{
	public:
		void Execute();
		virtual const char *FilterName(){return "LRCombine";} 
};

class TBCombine : public Filter
{
	public:
		void Execute();
		virtual const char *FilterName(){return "TBCombine";} 
};

class Blender : public Filter
{
	protected:
		double factor;
	public:
		void SetFactor(double f) { factor = f; }
		void Execute();
		virtual const char *FilterName(){return "Blender";} 
};

class Mirror : public Filter
{
	public:
		void Execute();
		virtual const char *FilterName(){return "Mirror";} 

};

class Rotate : public Filter
{
	public:
		void Execute();
		virtual const char *FilterName(){return "Rotate";} 

};

class Subtract : public Filter
{
	public:
		void Execute();
		virtual const char *FilterName(){return "Subtract";} 

};

class Grayscale : public Filter
{
	public:
		void Execute();
		virtual const char *FilterName(){return "Grayscale";} 

};

class Blur : public Filter
{
	public:
		void Execute();
		virtual const char *FilterName(){return "Blur";} 

};

class Color : public Source
{
	private:
		int width, height;
		unsigned char red, green, blue;
	public:
		Color(int width, int height, unsigned char r, unsigned char g, unsigned char b);
		void Execute();
		virtual const char *SourceName(){return "Color";}

};

class CheckSum : public Sink
{
	public:
		virtual void OutputCheckSum(const char *filename);
		virtual const char *SinkName(){return "CheckSum";}

};
