#include <source.h>
#include <sink.h>

class Filter : public Source, public Sink
{
	public:
		Filter(void);
};

class Shrinker : public Filter
{
	public:
		virtual void Execute();
};

class LRCombine : public Filter
{
	public:
		virtual void Execute(); 
};

class TBCombine : public Filter
{
	public:
		virtual void Execute();
};

class Blender : public Filter
{
	protected:
		double factor;
	public:
		void SetFactor(double f) { factor = f; }
		virtual void Execute();
};
