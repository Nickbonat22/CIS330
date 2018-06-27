#include <source.h>
#include <sink.h>

class Filter : public Source, public Sink
{
	public:
		Filter(void);
		virtual ~Filter(void);
		virtual void Update();
};

class Shrinker : public Filter
{
	public:
		virtual ~Shrinker(void);
		void Execute();
};

class LRCombine : public Filter
{
	public:
		virtual ~LRCombine(void);
		void Execute();
};

class TBCombine : public Filter
{
	public:
		virtual ~TBCombine(void);
		void Execute();
};

class Blender : public Filter
{
	protected:
		double factor;
	public:
		virtual ~Blender(void);
		void SetFactor(double f) { factor = f; }
		void Execute();
};
