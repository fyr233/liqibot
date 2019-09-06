#define CQAPPID "me.cqp.fyr233.repeat" //请修改AppID，规则见 http://d.cqp.me/Pro/开发/基础信息
#define CQAPPINFO CQAPIVERTEXT "," CQAPPID

CQEVENT(int32_t, __eventGroupMsg, 36)(int32_t subType, int32_t msgId, int64_t fromGroup, int64_t fromQQ, const char *fromAnonymous, const char *msg, int32_t font);
