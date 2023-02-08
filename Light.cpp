class Light {
    private:
        static Light* instance_;
        static Light* getInstance();
    public:
        void init(){
            
        }
};

Light *Light::getInstance(){
    if (instance_ == nullptr) {
        return nullptr;
    }
    return instance_;
}