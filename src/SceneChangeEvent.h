#ifndef SCENECHANGEEVENT_H
#define SCENECHANGEEVENT_H

class SceneChangeEvent
{
	public:
		enum Reason : int
		{
			Unspecified = 0,
			GameStarted,
			// ...
		};
		
		SceneChangeEvent();
		SceneChangeEvent( Reason theReason );
		
		Reason reason;
		union
		{
			// ...
		};
};

#endif // SCENECHANGEEVENT_H
