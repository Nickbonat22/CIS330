#include <source.h>
#include <sink.h>

class Filter : public Source, public Sink
{
	public:
		Filter(void);
		virtual void Update();
		virtual const char *SourceName();
		virtual const char *SinkName();
		virtual const char *FilterName() = 0;
};

class Shrinker : public Filter
{
	public:
		virtual void Execute();
		virtual const char *FilterName(){return "Shrinker";}
};

class LRCombine : public Filter
{
	public:
		virtual void Execute();
		virtual const char *FilterName(){return "LRCombine";} 
};

class TBCombine : public Filter
{
	public:
		virtual void Execute();
		virtual const char *FilterName(){return "TBCombine";} 
};

class Blender : public Filter
{
	protected:
		double factor;
	public:
		void SetFactor(double f) { factor = f; }
		virtual void Execute();
		virtual const char *FilterName(){return "Blender";} 
};
