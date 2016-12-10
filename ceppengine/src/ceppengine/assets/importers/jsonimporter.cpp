#include "jsonimporter.h"
#include "../../util/thirdparty/json/json.h"
#include "../material.h"
#include "../sprite.h"
#include "../spriteanimation.h"
#include "../../engine.h"

namespace cepp {

JsonImporter::JsonImporter()
{

}

bool JsonImporter::canLoadExtension(const std::string &extension) const
{
    return extension == ".sprite" || extension == ".material" || extension == ".spriteanim";
}

std::vector<Asset *> JsonImporter::import(std::istream &stream) const
{
    std::vector<Asset*> assets;

    Json::Value root;
    stream >> root;
    if(root.isObject()) {
        Asset *asset = createAsset(root);
        if(asset)
            assets.push_back(asset);
    }
    else if(root.isArray()) {
        for(int i = 0; i < root.size(); i++) {
            Asset *asset = createAsset(root.get(i, Json::Value()));
            if(asset)
                assets.push_back(asset);
        }
    }

    return assets;
}

Asset *JsonImporter::createAsset(const Json::Value &jObj) const
{
    if(!jObj.isObject())
        return 0;

    std::string type = jObj.get("type", "Invalid").asString();
    if(type == "Material") {
        Material *mat = new Material();

        Shader *shader = (Shader*)Engine::instance()->assetLoader()->loadAsset(jObj.get("shader", "").asString(), "Shader");
        mat->setShader(shader);
        Texture *tex = (Texture*)Engine::instance()->assetLoader()->loadAsset(jObj.get("texture", "").asString(), "Texture");
        mat->setTexture(tex);

        Json::Value params = jObj.get("shaderParameters", Json::Value());
        if(!params.isArray())
            return mat;

        for(int i = 0; i < params.size(); i++) {
            Json::Value param = params.get(i, Json::Value());
            if(!param.isObject()) continue;
            std::string name = param.get("name", "Undefined").asString();
            Json::Value value = param.get("value", Json::Value());
            if(!value.isArray()) continue;
            float *fValue = new float[value.size()];
            for(int ii = 0; ii < value.size(); ii++)
                fValue[ii] = value.get(ii, 0.f).asFloat();
            mat->setShaderParam(name, fValue, value.size());
            delete fValue;
        }

        return mat;
    }
    else if(type == "Sprite") {
        Sprite *sprite = new Sprite();

        Texture *tex = (Texture*)Engine::instance()->assetLoader()->loadAsset(jObj.get("texture", "").asString(), "Texture");
        sprite->setTexture(tex);

        Json::Value jPivot = jObj.get("pivot", Json::Value());
        if(jPivot.isArray() && jPivot.size() >= 2)
            sprite->setPivot(Vector3(jPivot.get(Json::ArrayIndex(0), 0.f).asFloat(), jPivot.get(Json::ArrayIndex(1), 0.f).asFloat(), jPivot.get(Json::ArrayIndex(2), 0.f).asFloat()));

        Json::Value jTexCoords = jObj.get("textureCoordinates", Json::Value());
        if(jTexCoords.isArray() && jTexCoords.size() >= 2)
            sprite->setTextureCoordinates(Vector3(jTexCoords.get(Json::ArrayIndex(0), 0.f).asFloat(), jTexCoords.get(Json::ArrayIndex(1), 0.f).asFloat(), jTexCoords.get(Json::ArrayIndex(2), 0.f).asFloat()));

        Json::Value jSize = jObj.get("size", Json::Value());
        if(jSize.isArray() && jSize.size() >= 2)
            sprite->setSize(Vector3(jSize.get(Json::ArrayIndex(0), 0.f).asFloat(), jSize.get(Json::ArrayIndex(1), 0.f).asFloat(), jSize.get(Json::ArrayIndex(2), 0.f).asFloat()));

        sprite->setPixelsPerUnit(jObj.get("pixelsPerUnit", 1.f).asFloat());

        return sprite;
    }
    else if(type == "SpriteAnimation") {
        Json::Value jFrames = jObj.get("frames", Json::Value());
        std::vector<SpriteAnimation::Frame> frames;
        if(jFrames.isArray()) {
            for(int i = 0; i < jFrames.size(); i++) {
                Json::Value jFrame = jFrames.get(i, Json::Value());
                if(!jFrame.isObject()) continue;
                SpriteAnimation::Frame f;
                f.duration = jFrame.get("duration", 0.f).asFloat();
                f.sprite = (Sprite*)Engine::instance()->assetLoader()->loadAsset(jFrame.get("sprite", "").asString(), "Sprite");
                frames.push_back(f);
            }
        }

        bool loop = jObj.get("loop", false).asBool();
        SpriteAnimation *anim = new SpriteAnimation(frames);
        anim->setLoop(loop);
        return anim;
    }
    else {
        return 0;
    }
}

} // namespace cepp
