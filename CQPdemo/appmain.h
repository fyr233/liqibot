#define CQAPPID "me.cqp.fyr233.repeat" //���޸�AppID������� http://d.cqp.me/Pro/����/������Ϣ
#define CQAPPINFO CQAPIVERTEXT "," CQAPPID

CQEVENT(int32_t, __eventGroupMsg, 36)(int32_t subType, int32_t msgId, int64_t fromGroup, int64_t fromQQ, const char *fromAnonymous, const char *msg, int32_t font);
