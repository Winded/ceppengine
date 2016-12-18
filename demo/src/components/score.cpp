#include "score.h"
#include <ceppengine/gameobject.h>

using namespace cepp;

Score::Score() : mScore(0)
{

}

std::string Score::typeName() const
{
    return "Score";
}

int Score::score() const
{
    return mScore;
}

void Score::setScore(int score)
{
    mScore = score;
    mText->setText(std::to_string(mScore));
}

void Score::addScore(int score)
{
    setScore(mScore + score);
}

void Score::start()
{
    mText = (UIText*)gameObject()->getComponent("UIText");
    mText->setText(std::to_string(mScore));
}
