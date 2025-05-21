enum SmileyType {
    SMILEY_TYPE_NONE = 0,
    SMILEY_TYPE_ANGRY,
    SMILEY_TYPE_SAD,
    SMILEY_TYPE_MEH,
    SMILEY_TYPE_HAPPY,
    SMILEY_TYPE_END
};

inline const char* SmileyTypeToString(SmileyType type) {
    switch (type) {
        case SMILEY_TYPE_ANGRY: return "Angry";
        case SMILEY_TYPE_SAD: return "Sad";
        case SMILEY_TYPE_MEH: return "Meh";
        case SMILEY_TYPE_HAPPY: return "Happy";
        default: return "None";
    }
}