#pragma once

#include <ceppengine/components/component.h>
#include <ceppengine/components/ui/uitext.h>

class Score : public cepp::Component
{
    public:
        Score();

        virtual std::string typeName() const;

        int score() const;
        void setScore(int score);

        void addScore(int score);

    protected:
        virtual void start();

    private:
        cepp::Ref<cepp::UIText> mText;

        int mScore;
};
