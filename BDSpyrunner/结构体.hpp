#pragma once
//-----------------------
// �ṹ�嶨��
//-----------------------
#include "Ԥ����ͷ.h"
using namespace std;
// �������ṹ��
struct Vec3 {
	float x, y, z;
};
struct BlockLegacy {
	string getBlockName() {
		return *(string*)((__int64)this + 112);
	}
	// ��ȡ����ID��
	auto getBlockItemID() const {			// IDA VanillaItems::initCreativeItemsCallback Item::beginCreativeGroup "itemGroup.name.planks"
		short v3 = *(short*)((VA)this + 268);
		if (v3 < 0x100) {
			return v3;
		}
		return (short)(255 - v3);
	}

};
struct Block {
	BlockLegacy* getBlockLegacy() {
		return SymCall(BlockLegacy*,"?getLegacyBlock@Block@@QEBAAEBVBlockLegacy@@XZ",
			 Block*)(this);
	}
};
struct BlockPos {
	int x, y, z;
};
struct BlockSource {
	Block* getBlock(BlockPos* bp) {
		return SymCall(Block*,"?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z",
			 BlockSource*, BlockPos*)(this, bp);
	}
};
struct Actor {
	// ��ȡ����������Ϣ
	string getNameTag() {
		return SymCall(string&,"?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
			 Actor*)(this);
	}
	// ��ȡ���ﵱǰ����ά��ID
	int getDimensionId() {
		int dimensionId;
		SymCall(int&,"?getDimensionId@Actor@@UEBA?AV?$AutomaticID@VDimension@@H@@XZ",
			 Actor*, int*)(this, &dimensionId);
		return dimensionId;
	}
	// ��ȡ���ﵱǰ��������
	Vec3* getPos() {
		return SymCall(Vec3*,"?getPos@Actor@@UEBAAEBVVec3@@XZ",
			 Actor*)(this);
	}

};
struct Mob : Actor {

};
struct Player : Mob {
	// �������ݰ�
	VA sendPacket(VA pkt) {
		return SymCall(VA,"?sendNetworkPacket@ServerPlayer@@UEBAXAEAVPacket@@@Z",
			 Player*, VA)(this, pkt);
	}
};
struct ItemStackBase {
	VA vtable;
	VA mItem;
	VA mUserData;
	VA mBlock;
	short mAuxValue;
	char mCount;
	char mValid;
	char unk[4]{ 0 };
	VA mPickupTime;
	char mShowPickUp;
	char unk2[7]{ 0 };
	std::vector<VA*> mCanPlaceOn;
	VA mCanPlaceOnHash;
	std::vector<VA*> mCanDestroy;
	VA mCanDestroyHash;
	VA mBlockingTick;
	ItemStackBase* mChargedItem;
	VA uk;
public:
	/*VA save() {
		VA* cp = new VA[8]{ 0 };
		return SymCall(VA, MSSYM_MD5_e02d5851c93a43bfe24a4396ecb87cde, this, cp);
	}*/
#if (COMMERCIAL)
	Json::Value toJson() {
		VA t = save();
		Json::Value jv = (*(Tag**)t)->toJson();
		(*(Tag**)t)->clearAll();
		*(VA*)t = 0;
		delete (VA*)t;
		return jv;
	}
	void fromJson(Json::Value& jv) {
		VA t = Tag::fromJson(jv);
		SymCall(VA, MSSYM_B1QA7fromTagB1AA9ItemStackB2AAA2SAB1QA3AV1B1AE15AEBVCompoundTagB3AAAA1Z, this, *(VA*)t);
		(*(Tag**)t)->clearAll();
		*(VA*)t = 0;
		delete (VA*)t;
	}
	void fromTag(VA t) {
		SymCall(VA, MSSYM_B1QA7fromTagB1AA9ItemStackB2AAA2SAB1QA3AV1B1AE15AEBVCompoundTagB3AAAA1Z, this, t);
}
#endif
	/*bool getFromId(short id, short aux, char count) {
		memcpy(this, SYM_POINT(void, MSSYM_B1QA5EMPTYB1UA4ITEMB1AA9ItemStackB2AAA32V1B1AA1B), 0x90);
		bool ret = SymCall(bool, MSSYM_B2QUA7setItemB1AE13ItemStackBaseB2AAA4IEAAB1UA2NHB1AA1Z, this, id);
		mCount = count;
		mAuxValue = aux;
		mValid = true;
		return ret;
	}*/
};
struct ItemStack : ItemStackBase {
	// ȡ��ƷID
	short getId() {
		return SymCall(short,"?getId@ItemStackBase@@QEBAFXZ",
			 ItemStack*)(this);
	}
	// ȡ��Ʒ����ֵ
	short getAuxValue() {
		return SymCall(short,"?getAuxValue@ItemStackBase@@QEBAFXZ",
			 ItemStack*)(this);
	}
	// ȡ��Ʒ����
	std::string getName() {
		std::string str;
		SymCall(__int64,"?getName@ItemStackBase@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
			 ItemStack*, string*)(this, &str);
		return str;
	}
	// ȡ����������
	int getStackSize() {			// IDA ContainerModel::networkUpdateItem
		return *((char*)this + 34);
	}
	// �ж��Ƿ������
	/*bool isNull() {
		return SymCall(bool,
			MSSYM_B1QA6isNullB1AE13ItemStackBaseB2AAA4QEBAB1UA3NXZ,
			this);
	}*/
};
struct TextPacket {
	char filler[0xC8];
	// ȡ�����ı�
	std::string toString() {			// IDA ServerNetworkHandler::handle
		std::string str = std::string(*(std::string*)((VA)this + 80));
		return str;
	}
};

struct CommandRequestPacket {
	char filler[0x90];
	// ȡ�����ı�
	std::string toString() {			// IDA ServerNetworkHandler::handle
		std::string str = std::string(*(std::string*)((VA)this + 40));
		return str;
	}
};

struct ModalFormRequestPacket {
	char filler[0x48];
};

struct ModalFormResponsePacket {
	// ȡ�����ID
	UINT getFormId() {
		return *(UINT*)((VA)this + 40);
	}
	// ȡѡ�����
	std::string getSelectStr() {
		std::string x = *(std::string*)((VA)this + 48);
		VA l = x.length();
		if (x.c_str()[l - 1] == '\n') {
			return l > 1 ? x.substr(0, l - 1) :
				x;
		}
		return x;
	}
};
