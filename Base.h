#pragma once
#include "ghidra_export.h"
#include "util.h"
#include "loader.h"
#include <map>

using namespace std;
using namespace loader;

extern "C" long long _stdcall Navigation(float*, float*, float*);

namespace Base {
	namespace ModConfig {
		//���ò���
		bool GameDataInit = false;
		bool InitErrInfo = true;
		int InitErrCount = 0;
		//�����ò���
		string ModName = "Blink";
		string ModAuthor = "Alcedo";
		string ModVersion = "v1.0";
		string Version = "421470";
	}
	//��Ϸ��ַ����
	namespace BasicGameData {
		void* PlayerPlot = nullptr;
		void* ActionPlot = nullptr;
		void* MapPlot = nullptr;
		void* GameTimePlot = nullptr;
	}
	//������Ϣ
	namespace World {
		//��������
		namespace EnvironmentalData {
			//��������
			namespace TempData {
				void* t_environmental = nullptr;
				vector<void*> t_environmentalMessages;
			}

			struct EnvironmentalData {
				void* Plot = nullptr;
				float CoordinatesX = 0;
				float CoordinatesY = 0;
				float CoordinatesZ = 0;
				int Id = 0;
				int SubId = 0;
			};
			//���������б�
			map<void*, EnvironmentalData> Environmentals;
		}
		int MapId = 0;
	}
	//��ʱ��
	namespace Chronoscope {
		struct ChronoscopeData {
			float StartTime = 0;
			float EndTime = 0;
		};

		//���ڵ�ʱ��
		float NowTime = 0;
		//��ʱ���б�
		map<string, ChronoscopeData> ChronoscopeList;
		//��Ӽ�ʱ��(ʱ������ʱ�����ƣ��Ƿ񸲸�)
		static bool AddChronoscope(float duration, string name, bool Overlay = false) {
			if (ChronoscopeList.find(name) == ChronoscopeList.end() || Overlay) {
				ChronoscopeList[name].EndTime = NowTime + duration;
				ChronoscopeList[name].StartTime = NowTime;
				return true;
			}
			else
				return false;
		}
		//ɾ����ʱ��
		static void DelChronoscope(string name) {
			if (ChronoscopeList.find(name) != ChronoscopeList.end()) {
				ChronoscopeList.erase(name);
			}
		}
		//����ʱ��
		static bool CheckChronoscope(string name) {
			if (ChronoscopeList.find(name) != ChronoscopeList.end()) {
				if (ChronoscopeList[name].EndTime > NowTime)
					return true;
				else {
					return false;
				}
			}
			else {
				return false;
			}
				
		}
	}
	//����
	namespace Calculation {
		struct Vector3 {
			float x, y, z;
			Vector3(float x = 0, float y = 0, float z = 0) :x(x), y(y), z(z) {
			};
		};
		struct Vector2 {
			float x, y;
			Vector2(float x = 0, float y = 0) :x(x), y(y){
			};
		};
		Vector3 GetVector(Vector3 p1, Vector3 p2, float l) {
			float a = (p2.x - p1.x);
			float b = (p2.y - p1.y);
			float c = (p2.z - p1.z);
			l = l * l / (a * a + b * b + c * c);
			float k = sqrt(l);
			float newx1 = k * a + p1.x;
			float newy1 = k * b + p1.y;
			float newz1 = k * c + p1.z;
			return Vector3(newx1, newy1, newz1);
		}
		Vector2 GetExtensionVector2D(Vector2 Coordinate,float r, float angle) {
			float x, y;
			x = Coordinate.x + r * cos((4 * atan(1.0) / 180 * angle));
			y = Coordinate.y + r * sin((4 * atan(1.0) / 180 * angle));
			return Vector2(x, y);
		}
	}
	//������Ϣ
	namespace Monster {
		struct MonsterData {
			void* Plot = nullptr;
			float CoordinatesX = 0;
			float CoordinatesY = 0;
			float CoordinatesZ = 0;
			int Id = 0;
			int SubId = 0;
		};
		//���������б�
		map<void*, MonsterData> Monsters;
	}
	//�����Ϣ
	namespace PlayerData {
		//����
		namespace Coordinate {
			struct Coordinate {
				float x, y, z;
				Coordinate(float x = 0, float y = 0, float z = 0) :x(x), y(y), z(z) {
				};
			};
			//�������
			Coordinate Entity;
			//׼������
			Coordinate Collimator;
			//��ײ��������
			Coordinate Collision;
			//��������
			Coordinate Increment;
			//��������
			Coordinate Navigation;
			//��Ҵ���(X����,Y����,Z����,�Ƿ�ǽ)
			static void TransportCoordinate(float X, float Y, float Z, bool Across = false) {
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x160) = X;
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x164) = Y;
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x168) = Z;
				if (Across) {
					*offsetPtr<float>(BasicGameData::PlayerPlot, 0xA50) = X;
					*offsetPtr<float>(BasicGameData::PlayerPlot, 0xA54) = Y;
					*offsetPtr<float>(BasicGameData::PlayerPlot, 0xA58) = Z;
				}
			}
		}
		//��Ч
		namespace Effects {
			//������Ч(��Ч�飬��Чid)
			static void GenerateSpecialEffects(int group, int record) {
				//���������õ�����������ַ�б�
				void* EffectsPlot = *(undefined**)MH::Player::EffectsBasePlot;
				void* EffectsOffset1 = *offsetPtr<undefined**>((undefined(*)())EffectsPlot, 0x80);
				void* EffectsOffset2 = *offsetPtr<undefined**>((undefined(*)())EffectsOffset1, 0xC0);
				void* EffectsOffset3 = *offsetPtr<undefined**>((undefined(*)())EffectsOffset2, 0x38);
				void* EffectsOffset4 = *offsetPtr<undefined**>((undefined(*)())EffectsOffset3, 0x58);
				void* EffectsOffset5 = *offsetPtr<undefined**>((undefined(*)())EffectsOffset4, 0x40);
				void* Effects = offsetPtr<void*>(EffectsOffset5, 0xD10);
				//��Ч���
				MH::Player::Effects((undefined*)Effects, group, record);
			}
		}
		//����Ƕ�
		float Angle;
		//���򻡶�
		float Radian;
		//�Ƿ�����׼״̬
		bool AimingState;
		//���һ�λ��еĹ����ַ
		void* AttackMonsterPlot = nullptr;
	}
	//������Ϣ
	namespace Keyboard {
		namespace TempData {
			map<int, bool> t_KeyDown;
			map<int, int> t_KeyCount;
		}
		//������
		static void ClearKey() {
			for (auto [Environmental, EData] : World::EnvironmentalData::Environmentals) {
				if (EData.Plot == nullptr) {
					World::EnvironmentalData::Environmentals.erase(Environmental);
				}
			}
		}
		//�������
		static bool CheckKey(int vk, int ComboClick = 1,float Duration = 0.3) {
			//������������
			if (TempData::t_KeyDown.find(vk) == TempData::t_KeyDown.end()) {
				TempData::t_KeyDown[vk] = false;
			}
			//�������
			if (GetKeyState(vk) < 0 and !TempData::t_KeyDown[vk]) {
				TempData::t_KeyDown[vk] = true;
				//�������
				if (TempData::t_KeyCount.find(vk) != TempData::t_KeyCount.end()) {
					//��ʱ�����
					if(TempData::t_KeyCount[vk] == 1)
						Chronoscope::AddChronoscope(Duration, "KEY_" + to_string(vk), true);
					else if (!Chronoscope::CheckChronoscope("KEY_" + to_string(vk))) {
						TempData::t_KeyCount[vk] = 0;
					}
					TempData::t_KeyCount[vk]++;
				}
				else {
					Chronoscope::AddChronoscope(Duration, "KEY_" + to_string(vk), true);
					TempData::t_KeyCount[vk] = 1;
				}

				//�����
				if (TempData::t_KeyCount[vk] == ComboClick)
					return true;
				else
					return false;
			}
			else if(GetKeyState(vk) >= 0)
				TempData::t_KeyDown[vk] = false;
			return false;
		}
	}
	//��ʼ��
	static bool Init() {
		if (!ModConfig::GameDataInit) {
			void* PlayerPlot = *(undefined**)MH::Player::PlayerBasePlot;
			BasicGameData::PlayerPlot = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
			BasicGameData::ActionPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x468);
			BasicGameData::GameTimePlot = (undefined(*)())MH::World::GmaeClock;
			BasicGameData::MapPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7D20);
			if (
				BasicGameData::PlayerPlot != nullptr and
				BasicGameData::ActionPlot != nullptr and
				BasicGameData::MapPlot != nullptr and
				BasicGameData::GameTimePlot != nullptr
				) {
				//��������
				MH_Initialize();
				//�������ݻ�ȡ
				HookLambda(MH::World::WaypointZLocal,
					[](auto x1, auto x2) {
						Navigation(
							&Base::PlayerData::Coordinate::Navigation.x,
							&Base::PlayerData::Coordinate::Navigation.y,
							&Base::PlayerData::Coordinate::Navigation.z
						);
						return original(x1, x2);
					});
				//���������ַ��ȡ
				HookLambda(MH::EnvironmentalBiological::ctor,
					[](auto rcx, auto rdx, auto r8, auto r9) {
						Base::World::EnvironmentalData::TempData::t_environmental = rcx;
						return original(rcx, rdx, r8, r9);
					});
				HookLambda(MH::EnvironmentalBiological::ctor_,
					[](auto unkn1) {
						bool addEnvironmental = true;
						vector<void*>::iterator it;
						for (it = Base::World::EnvironmentalData::TempData::t_environmentalMessages.begin(); it != Base::World::EnvironmentalData::TempData::t_environmentalMessages.end(); it++)
						{
							if (*it == Base::World::EnvironmentalData::TempData::t_environmental)
								addEnvironmental = false;
						}
						if (addEnvironmental)
							Base::World::EnvironmentalData::TempData::t_environmentalMessages.push_back(Base::World::EnvironmentalData::TempData::t_environmental);
						return original(unkn1);
					});
				//�����ַ��ȡ
				HookLambda(MH::Monster::ctor,
					[](auto monster, auto id, auto subId) {
						auto ret = original(monster, id, subId);
						Base::Monster::Monsters[monster].Plot = monster;
						Base::Monster::Monsters[monster].CoordinatesX = *offsetPtr<float>(monster, 0x160);
						Base::Monster::Monsters[monster].CoordinatesY = *offsetPtr<float>(monster, 0x164);
						Base::Monster::Monsters[monster].CoordinatesZ = *offsetPtr<float>(monster, 0x168);
						Base::Monster::Monsters[monster].Id = id;
						Base::Monster::Monsters[monster].SubId = subId;
						return ret;
					});
				HookLambda(MH::Monster::dtor,
					[](auto monster) {
						Base::Monster::Monsters.erase(monster);
						return original(monster);
					});
				MH_ApplyQueued();
				ModConfig::GameDataInit = true;
				LOG(INFO) << ModConfig::ModName << " : Game data initialization complete!";
				LOG(INFO) << " |  Mod��" << ModConfig::ModName;
				LOG(INFO) << " |  Author��" << ModConfig::ModAuthor;
				LOG(INFO) << " |  Version��" << ModConfig::ModVersion;
				return true;
			}
			else {
				if (ModConfig::InitErrInfo) {
					LOG(ERR) << ModConfig::ModName << " : Game data initialization failed!";
					LOG(ERR) << "The following address failed to complete the initialization. We will try again later. If the address is still not initialized successfully, please contact the mod author for solution.";
					if (BasicGameData::PlayerPlot == nullptr)
						LOG(ERR) << " |  PlayerPlot";
					if (BasicGameData::ActionPlot == nullptr)
						LOG(ERR) << " |  ActionPlot";
					if (BasicGameData::MapPlot == nullptr)
						LOG(ERR) << " |  MapPlot";
					if (BasicGameData::GameTimePlot == nullptr)
						LOG(ERR) << " |  GameTimePlot";

					ModConfig::InitErrCount++;
					if (ModConfig::InitErrCount > 10)
						ModConfig::InitErrInfo = false;
				}
				return false;
			}
		}
		else
			return true;
	}
	//ʵʱ���µ�����
	static void RealTimeUpdate() {
		if (ModConfig::GameDataInit) {
			//ʵʱ���µ�ͼ��ַ��Ϣ
			BasicGameData::MapPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7D20);
			//д���ͼ��Ϣ���������
			if (World::MapId != *offsetPtr<int>(BasicGameData::MapPlot, 0xB88)) {
				World::MapId = *offsetPtr<int>(BasicGameData::MapPlot, 0xB88);
				//�����ʱ������
				Chronoscope::ChronoscopeList.clear();
				//���������������
				World::EnvironmentalData::TempData::t_environmentalMessages.clear();
				World::EnvironmentalData::Environmentals.clear();
				//���µ�ַ��Ϣ
				void* PlayerPlot = *(undefined**)MH::Player::PlayerBasePlot;
				BasicGameData::PlayerPlot = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
				BasicGameData::ActionPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x468);
			}
			//��������Ļ�������
			for (auto [Environmental, EData] : World::EnvironmentalData::Environmentals) {
				if (EData.Plot == nullptr) {
					World::EnvironmentalData::Environmentals.erase(Environmental);
				}
			}
			//�����������
			PlayerData::Angle = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x198) * 180.0;
			PlayerData::Radian = 4 * atan(1.0) / 180 * PlayerData::Angle;
			PlayerData::Coordinate::Entity.x = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x160);
			PlayerData::Coordinate::Entity.y = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x164);
			PlayerData::Coordinate::Entity.z = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x168);
			PlayerData::Coordinate::Collision.x = *offsetPtr<float>(BasicGameData::PlayerPlot, 0xA50);
			PlayerData::Coordinate::Collision.x = *offsetPtr<float>(BasicGameData::PlayerPlot, 0xA54);
			PlayerData::Coordinate::Collision.x = *offsetPtr<float>(BasicGameData::PlayerPlot, 0xA58);
			PlayerData::Coordinate::Collimator.x = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D30);
			PlayerData::Coordinate::Collimator.x = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D34);
			PlayerData::Coordinate::Collimator.x = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D38);
			void* IncrementPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x468);
			if (IncrementPlot != nullptr) {
				PlayerData::Coordinate::Increment.x = *offsetPtr<float>(IncrementPlot, 0x7D30);
				PlayerData::Coordinate::Increment.x = *offsetPtr<float>(IncrementPlot, 0x7D34);
				PlayerData::Coordinate::Increment.x = *offsetPtr<float>(IncrementPlot, 0x7D38);
			}
			else {
				PlayerData::Coordinate::Increment.x = 0.0;
				PlayerData::Coordinate::Increment.x = 0.0;
				PlayerData::Coordinate::Increment.x = 0.0;
			}
			void* AimingStatePlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0xC0);
			if (AimingStatePlot != nullptr)
				PlayerData::AimingState = *offsetPtr<bool>(AimingStatePlot, 0xC28);
			else
				PlayerData::AimingState = false;
			void* AttackMonsterPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x4C0);
			void* AttackMonsterOffset1 = *offsetPtr<undefined**>((undefined(*)())AttackMonsterPlot, 0x98);
			void* AttackMonsterOffset2 = *offsetPtr<undefined**>((undefined(*)())AttackMonsterOffset1, 0xD8);
			PlayerData::AttackMonsterPlot = *offsetPtr<void*>(AimingStatePlot, 0x4298);

			//���»�����������
			vector<void*>::iterator it;
			for (it = World::EnvironmentalData::TempData::t_environmentalMessages.begin(); it != World::EnvironmentalData::TempData::t_environmentalMessages.end(); it++)
			{
				if (*it != nullptr) {

					if (Base::World::EnvironmentalData::Environmentals.find(*it) == Base::World::EnvironmentalData::Environmentals.end()) {
						Base::World::EnvironmentalData::Environmentals[*it].Plot = *it;
						Base::World::EnvironmentalData::Environmentals[*it].CoordinatesX = *offsetPtr<float>(*it, 0x160);
						Base::World::EnvironmentalData::Environmentals[*it].CoordinatesY = *offsetPtr<float>(*it, 0x164);
						Base::World::EnvironmentalData::Environmentals[*it].CoordinatesZ = *offsetPtr<float>(*it, 0x168);
						Base::World::EnvironmentalData::Environmentals[*it].Id = *offsetPtr<int>(*it, 0x1AF0);
						Base::World::EnvironmentalData::Environmentals[*it].SubId = *offsetPtr<int>(*it, 0x1AF4);
					}
					else {
						//�����������б��о�ֻ������������
						Base::World::EnvironmentalData::Environmentals[*it].CoordinatesX = *offsetPtr<float>(*it, 0x160);
						Base::World::EnvironmentalData::Environmentals[*it].CoordinatesY = *offsetPtr<float>(*it, 0x164);
						Base::World::EnvironmentalData::Environmentals[*it].CoordinatesZ = *offsetPtr<float>(*it, 0x168);
					}
				}
				else {
					World::EnvironmentalData::TempData::t_environmentalMessages.erase(it);
				}
			}
			//���¹�����Ϣ
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					Base::Monster::Monsters[monster].CoordinatesX = *offsetPtr<float>(monster, 0x160);
					Base::Monster::Monsters[monster].CoordinatesY = *offsetPtr<float>(monster, 0x164);
					Base::Monster::Monsters[monster].CoordinatesZ = *offsetPtr<float>(monster, 0x168);
				}
			}
			//���¼�ʱ��ʱ��
			Chronoscope::NowTime = *offsetPtr<float>(BasicGameData::MapPlot, 0xC24);
		}
	}
}