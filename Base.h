#pragma once
#include "ghidra_export.h"
#include "util.h"
#include "loader.h"
#include <map>
#include "MonsterBuff.h"
#include "PlayerBuff.h"

using namespace std;
using namespace loader;

extern "C" long long _stdcall Navigation(float*, float*, float*);
extern "C" void* _stdcall GetVisualPtr(void*);

namespace Base {
	//���ýṹ
	struct Vector3 {
		float x, y, z;
		Vector3(float x = 0, float y = 0, float z = 0) :x(x), y(y), z(z) {
		};
	};
	struct Vector2 {
		float x, y;
		Vector2(float x = 0, float y = 0) :x(x), y(y) {
		};
	};
#pragma region ModConfig
	namespace ModConfig {
		//���ò���
		bool GameDataInit = false;
		bool InitErrInfo = true;
		int InitErrCount = 0;
		//�����ò���
		string ModName = "LuaScript";
		string ModAuthor = "Alcedo";
		string ModVersion = "v1.0.9";
		string Version = "421470";
	}
#pragma endregion
	//��Ϸ������ַ
#pragma region BasicGameData
	//��Ϸ��ַ����
	namespace BasicGameData {
		void* PlayerPlot = nullptr;
		void* PlayerInfoPlot = nullptr;
		void* ActionPlot = nullptr;
		void* MapPlot = nullptr;
		void* GameTimePlot = nullptr;
	}
#pragma endregion
	//������Ϣ
#pragma region World
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
				EnvironmentalData(
					void* Plot = nullptr,
					float CoordinatesX = 0,
					float CoordinatesY = 0,
					float CoordinatesZ = 0,
					int Id = 0,
					int SubId = 0)
					:Plot(Plot), CoordinatesX(CoordinatesX), CoordinatesY(CoordinatesY), CoordinatesZ(CoordinatesZ), Id(Id), SubId(SubId) {
				};
			};
			//���������б�
			map<void*, EnvironmentalData> Environmentals;
			//����ɸѡ��
			pair<int, int> Filter(255, 255);
		}
		int MapId = 0;
	}
#pragma endregion
	//��ʱ��
#pragma region Chronoscope
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
		//����ʱ���Ƿ����
		static bool CheckPresenceChronoscope(string name) {
			if (ChronoscopeList.find(name) != ChronoscopeList.end()) {
				return true;
			}
			return false;
		}
		//����ʱ���Ƿ�������
		static bool CheckChronoscope(string name) {
			if (ChronoscopeList.find(name) != ChronoscopeList.end()) {
				if (ChronoscopeList[name].EndTime > NowTime)
					return true;
			}
			return false;
		}
	}
#pragma endregion
	//����
#pragma region Calculation
	namespace Calculation {
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
		float myRander(float min, float max)
		{
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_real_distribution<float> dist(min, max);
			return dist(eng);
		}
		float DistanceBetweenTwoCoordinates(Vector3 point1, Vector3 point2) {
			float RangeDistance = sqrt((point1.x - point2.x) * (point1.x - point2.x)) + sqrt((point1.z - point2.z) * (point1.z - point2.z));
			RangeDistance = sqrt((RangeDistance * RangeDistance) + sqrt((point1.y - point2.y) * (point1.y - point2.y)));
			return RangeDistance;
		}
	}
#pragma endregion
	//ͼ�λ���
#pragma region Draw
	namespace Draw {
		HWND GameHandle;
		bool HandleInit = false;
		//��ʼ��ͼ�λ���
		static void InitDraw() {
			string GameName = "MONSTER HUNTER: WORLD(" + ModConfig::Version + ")";
			GameHandle = FindWindow(NULL, GameName.c_str());
			if(GameHandle != nullptr)
				HandleInit = true;
		}
		//���� ������
		static void Draw() {
			HDC hdc = ::GetDC(GameHandle);
			RECT rect;
			::GetWindowRect(GameHandle, &rect);
			::MoveToEx(hdc, 0, 0, NULL);
			::LineTo(hdc, rect.right, rect.bottom);
			::MoveToEx(hdc, rect.right, 0, NULL);
			::LineTo(hdc, 0, rect.bottom);
			::ReleaseDC(GameHandle, hdc);
		}
	}
#pragma endregion
	//ί��
#pragma region Commission
	namespace Commission {
		namespace MoveEntity {
			struct Parameter {
				Vector3 Vector;
				void* Entity = nullptr;
				float speed = 100.0;
			};
			map<void*, Parameter> CommissionList;

			static void MoveEntityToTarget() {
				for (auto [entity, parameter] : CommissionList) {
					if (entity != nullptr) {
						//�ƶ���Ŀ��
						if (parameter.Entity != nullptr) {
							float EntityX = *offsetPtr<float>(entity, 0x160);
							float EntityY = *offsetPtr<float>(entity, 0x160);
							float EntityZ = *offsetPtr<float>(entity, 0x160);
							float ToEntityX = *offsetPtr<float>(parameter.Entity, 0x160);
							float ToEntityY = *offsetPtr<float>(parameter.Entity, 0x160);
							float ToEntityZ = *offsetPtr<float>(parameter.Entity, 0x160);

							if (fabs(ToEntityX - EntityX) > float(10)) {
								if (ToEntityX < EntityX)
									EntityX -= float(fabs(ToEntityX - EntityX) / 10);
								else
									EntityX += float(fabs(ToEntityX - EntityX) / 10);
							}
							else
								EntityX = ToEntityX;

							if (fabs(ToEntityY - EntityY) > float(10)) {
								if (ToEntityY < EntityY)
									EntityY -= float(fabs(ToEntityY - EntityY) / parameter.speed);
								else
									EntityY += float(fabs(ToEntityY - EntityY) / parameter.speed);
							}
							else
								EntityY = ToEntityY;

							if (fabs(ToEntityZ - EntityZ) > float(10)) {
								if (ToEntityZ < EntityZ)
									EntityZ -= float(fabs(ToEntityZ - EntityZ) / 10);
								else
									EntityZ += float(fabs(ToEntityZ - EntityZ) / 10);
							}
							else
								EntityZ = ToEntityZ;

							*offsetPtr<float>(entity, 0x160) = ToEntityX;
							*offsetPtr<float>(entity, 0x164) = ToEntityY;
							*offsetPtr<float>(entity, 0x168) = ToEntityZ;

							if (
								*offsetPtr<float>(entity, 0x160) == ToEntityX and
								*offsetPtr<float>(entity, 0x164) == ToEntityY and
								*offsetPtr<float>(entity, 0x168) == ToEntityZ
								)
								CommissionList.erase(entity);
						}
						//�ƶ�����
						else {
							float EntityX = *offsetPtr<float>(entity, 0x160);
							float EntityY = *offsetPtr<float>(entity, 0x160);
							float EntityZ = *offsetPtr<float>(entity, 0x160);
							float ToEntityX = parameter.Vector.x;
							float ToEntityY = parameter.Vector.y;
							float ToEntityZ = parameter.Vector.z;
							if (EntityX - ToEntityX > 10) {
								if (EntityX > ToEntityX)
									*offsetPtr<float>(entity, 0x160) -= (EntityX - ToEntityX) / parameter.speed;
								else
									*offsetPtr<float>(entity, 0x160) += (EntityX - ToEntityX) / parameter.speed;
							}
							else
								*offsetPtr<float>(entity, 0x160) = ToEntityX;
							if (EntityY - ToEntityY > 10) {
								if (EntityY > ToEntityY)
									*offsetPtr<float>(entity, 0x164) -= (EntityY - ToEntityY) / parameter.speed;
								else
									*offsetPtr<float>(entity, 0x164) += (EntityY - ToEntityY) / parameter.speed;
							}
							else
								*offsetPtr<float>(entity, 0x164) = ToEntityY;
							if (EntityZ - ToEntityZ > 10) {
								if (EntityZ > ToEntityZ)
									*offsetPtr<float>(entity, 0x168) -= (EntityZ - ToEntityZ) / parameter.speed;
								else
									*offsetPtr<float>(entity, 0x168) += (EntityZ - ToEntityZ) / parameter.speed;
							}
							else
								*offsetPtr<float>(entity, 0x168) = ToEntityZ;

							if (
								*offsetPtr<float>(entity, 0x160) == ToEntityX and
								*offsetPtr<float>(entity, 0x164) == ToEntityY and
								*offsetPtr<float>(entity, 0x168) == ToEntityZ
								)
								CommissionList.erase(entity);
						}
					}
				}
			}
		}

		static void CleanCommission() {
			MoveEntity::CommissionList.clear();
		}

		static void Run() {
			MoveEntity::MoveEntityToTarget();
		}
	}
#pragma endregion
	//������Ϣ
#pragma region Monster
	namespace Monster {
		struct MonsterData {
			void* Plot;
			float CoordinatesX;
			float CoordinatesY;
			float CoordinatesZ;
			int Id;
			int SubId;
			MonsterData(
				void* Plot = nullptr,
				float CoordinatesX = 0,
				float CoordinatesY = 0,
				float CoordinatesZ = 0,
				int Id = 0,
				int SubId = 0) 
				:Plot(Plot), CoordinatesX(CoordinatesX), CoordinatesY(CoordinatesY), CoordinatesZ(CoordinatesZ), Id(Id), SubId(SubId){
			};
		};
		//�����б�
		map<void*, MonsterData> Monsters;
		//����ɸѡ��
		pair<int, int> Filter(255,255);
		//����������buff
		static void SetBuff(void* monster,string buff){
			MonsterBuff::MonsterBuffState monsterBuff = MonsterBuff::GetMonsterBuffState(monster,buff);
			if (monsterBuff.MaxStateValue != 0) {
				MonsterBuff::SetMonsterBuffState(monster, buff);
			}
		}
		static void BehaviorControl(void* monster, int Fsm) {
			//��л�Ϸ��ʴ����ṩ�ĵ�ַ
			MH::Monster::BehaviorControl((undefined*)monster, Fsm);
		}
	}
#pragma endregion
	//�����Ϣ
#pragma region PlayerData
	namespace PlayerData {
		struct FsmData {
			//���� 0Ϊ����3Ϊ����
			int Target = 0;
			//ִ��Id
			int Id = 0;
			FsmData(int Target = 0, int Id = 0) :Target(Target), Id(Id) {
			};
		};

		//��������
		namespace TempData {
			FsmData t_ManualFsmAction;
			bool t_executingFsmAction = false;
		}

		//����
		namespace Coordinate {
			//��������
			namespace TempData {
				void* t_visual = nullptr;
				Vector3 t_SetVisualCoordinate;
				void* t_SetVisualBind = nullptr;
				bool t_SetVisual = false;
				bool t_LockVisual = false;
			}

			//�������
			Vector3 Entity;
			//׼������
			Vector3 Collimator;
			//��ײ��������
			Vector3 Collision;
			//��������
			Vector3 Increment;
			//��������
			Vector3 Navigation;
			//�������
			Vector3 Visual;
			//��������
			Vector3 Weapon;
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
				//��л�Ϸ��ʴ����ṩ�ĵ�ַ
				void* Effects = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x8808);
				//��Ч���
				MH::Player::Effects((undefined*)Effects, group, record);
			}
		}
		//�����
		static void SetVisual(void* bind, float Duration = 0) {
			if (Duration != 0)
				Chronoscope::AddChronoscope(Duration, "SetVisual", true);
			else
				Coordinate::TempData::t_LockVisual = true;
			Coordinate::TempData::t_SetVisualBind = bind;
			Coordinate::TempData::t_SetVisual = true;
		}
		//����������
		static void UnbindVisual() {
			Coordinate::TempData::t_LockVisual = false;
			Coordinate::TempData::t_SetVisual = false;
			Coordinate::TempData::t_SetVisualBind = nullptr;
		}
		//�������(X����,Y����,Z����,����ʱ��0=����)
		static void SetVisual(float X, float Y, float Z, float Duration = 0) {
			if (Duration != 0) {
				UnbindVisual();
				Chronoscope::AddChronoscope(Duration, "SetVisual", true);
			}
			else
				Coordinate::TempData::t_LockVisual = true;
			Coordinate::TempData::t_SetVisualCoordinate.x = X;
			Coordinate::TempData::t_SetVisualCoordinate.y = Y;
			Coordinate::TempData::t_SetVisualCoordinate.z = Z;
			Coordinate::TempData::t_SetVisual = true;
		}
		//����Ƕ�
		float Angle;
		//���򻡶�
		float Radian;
		//�������
		float VisualDistance;
		//�Ƿ�����׼״̬
		bool AimingState;
		//���һ�λ��еĹ����ַ
		void* AttackMonsterPlot = nullptr;
		//����id
		float ActionId;
		//��������
		int WeaponType;
		//����ID
		int WeaponId;
		//������Ϣ
		FsmData Fsm;
		//�������
		string Name;
		//hr�ȼ�
		int Hr;
		//mr�ȼ�
		int Mr;
		//��ǰѪ��
		float CurrentHealth;
		//����Ѫ����0-150��
		float BasicHealth;
		//Ѫ������
		float MaxHealth;
		//��ǰ����
		float CurrentEndurance;
		//�������ޣ�25-150��
		float MaxEndurance;

		//ִ����������(ִ�ж���,ִ��Id)
		static void RunDerivedAction(int type, int id) {
			TempData::t_ManualFsmAction = FsmData(type, id);
			TempData::t_executingFsmAction = true;
			*offsetPtr<int>(BasicGameData::PlayerPlot, 0x6284) = type;
			*offsetPtr<int>(BasicGameData::PlayerPlot, 0x6288) = id;
			*offsetPtr<int>(BasicGameData::PlayerPlot, 0x628C) = type;
			*offsetPtr<int>(BasicGameData::PlayerPlot, 0x6290) = id;
			Fsm = FsmData(type, id);
		}
		//���ִ�����������Ƿ����
		static bool CheckDerivedAction() {
			if (TempData::t_executingFsmAction) {
				if (Fsm.Id != TempData::t_ManualFsmAction.Id and Fsm.Target != TempData::t_ManualFsmAction.Target) {
					TempData::t_executingFsmAction = false;
					return true;
				}
				else
					return false;
			}
			return false;
		}
		//�����������������ͣ�����ID��
		static void ChangeWeapons(int type, int id) {
			if(type <= 13 and type >= 0 and id >= 0)
				MH::Weapon::ChangeWeapon(BasicGameData::PlayerPlot, type, id);
		}
		//��ȡ���Buff����ʱ��
		static float GetPlayerBuff(string buff) {
			void* BuffsPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x7D20);
			int buffPtr = PlayerBuff::GetBuffPtr(buff);
			return *offsetPtr<float>(BuffsPlot, buffPtr);
		}
		//�������Buff����ʱ��
		static void SetPlayerBuff(string buff, float duration) {
			void* BuffsPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x7D20);
			int buffPtr = PlayerBuff::GetBuffPtr(buff);
			*offsetPtr<float>(BuffsPlot, buffPtr) = duration;
		}
		//������ݸ���
		static void Updata() {
			Angle = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x198) * 180.0;
			Radian = 4 * atan(1.0) / 180 * PlayerData::Angle;
			Coordinate::Entity = Vector3(
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x160),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x164),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x168)
			);
			Coordinate::Collision = Vector3(
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0xA50),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0xA54),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0xA58)
			);
			Coordinate::Collimator = Vector3(
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D30),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D34),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D38)
			);
			void* WeaponEntityPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x76B0);
			if(WeaponEntityPlot != nullptr)
				Coordinate::Weapon = Vector3(
					*offsetPtr<float>(WeaponEntityPlot, 0x160),
					*offsetPtr<float>(WeaponEntityPlot, 0x164),
					*offsetPtr<float>(WeaponEntityPlot, 0x168)
				);
			VisualDistance = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x7690);
			Coordinate::Increment = Vector3(
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x1530),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x1534),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x1538));
			/*
			void* IncrementPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x468);
			if (IncrementPlot != nullptr) {
				Coordinate::Increment.x = *offsetPtr<float>(IncrementPlot, 0x7D30);
				Coordinate::Increment.y = *offsetPtr<float>(IncrementPlot, 0x7D34);
				Coordinate::Increment.z = *offsetPtr<float>(IncrementPlot, 0x7D38);
			}
			else {
				Coordinate::Increment.x = 0.0;
				Coordinate::Increment.y = 0.0;
				Coordinate::Increment.z = 0.0;
			}
			*/
			void* AimingStatePlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0xC0);
			if (AimingStatePlot != nullptr)
				AimingState = *offsetPtr<bool>(AimingStatePlot, 0xC28);
			else
				AimingState = false;
			void* AttackMonsterOffset1 = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x4C0);
			void* AttackMonsterOffset2 = *offsetPtr<undefined**>((undefined(*)())AttackMonsterOffset1, 0x98);
			void* AttackMonsterOffset3 = *offsetPtr<undefined**>((undefined(*)())AttackMonsterOffset2, 0xD8);
			AttackMonsterPlot = *offsetPtr<undefined**>((undefined(*)())AttackMonsterOffset3, 0x4298);
			ActionId = *offsetPtr<int>(BasicGameData::ActionPlot, 0xE9C4);
			void* WeaponPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0xc0);
			void* WeaponOffset1 = *offsetPtr<undefined**>((undefined(*)())WeaponPlot, 0x8);
			void* WeaponOffset2 = *offsetPtr<undefined**>((undefined(*)())WeaponOffset1, 0x78);
			WeaponType = *offsetPtr<int>(WeaponOffset2, 0x2E8);
			WeaponId = *offsetPtr<int>(WeaponOffset2, 0x2EC);
			Fsm = FsmData(
				*offsetPtr<int>(BasicGameData::PlayerPlot, 0x628C),
				*offsetPtr<int>(BasicGameData::PlayerPlot, 0x6290)
			);
			BasicHealth = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x7628);
			void* StatusManagementPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7630);
			if (StatusManagementPlot != nullptr) {
				CurrentHealth = *offsetPtr<float>(StatusManagementPlot, 0x64);
				MaxHealth = *offsetPtr<float>(StatusManagementPlot, 0x60);
				CurrentEndurance = *offsetPtr<float>(StatusManagementPlot, 0x13C);
				MaxEndurance = *offsetPtr<float>(StatusManagementPlot, 0x144);
			}
			else {
				CurrentHealth = 0;
				MaxHealth = 0;
				CurrentEndurance = 0;
				MaxEndurance = 0;
			}
			Name = *offsetPtr<string>(BasicGameData::PlayerInfoPlot, 0x50);
			Hr = *offsetPtr<int>(BasicGameData::PlayerInfoPlot, 0x90);
			Mr = *offsetPtr<int>(BasicGameData::PlayerInfoPlot, 0xD4);
		}
	}
#pragma endregion
	//������Ϣ
#pragma region Keyboard
	namespace Keyboard {
		namespace TempData {
			map<int, bool> t_KeyDown;
			map<int, int> t_KeyCount;
		}
		//��鴰��
		static bool CheckWindows() {
			string GameName = "MONSTER HUNTER: WORLD(" + ModConfig::Version + ")";
			HWND wnd = GetForegroundWindow();;
			HWND mhd = FindWindow(NULL, GameName.c_str());
			if (wnd == mhd)
				return true;
			else
				return false;
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
			if (!CheckWindows())
				return false;
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
					if (!Chronoscope::CheckChronoscope("KEY_" + to_string(vk))) {
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
#pragma endregion
	//Ͷ����
#pragma region ProjectilesOperation
	namespace ProjectilesOperation {
		//ִ��Ͷ��������
		static bool CallProjectilesGenerate(int Id, float* Coordinate, int From = 0) {
			//����������Ͷ����
			void* Weapon = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x76B0);
			void* WeaponShlpPlot= *offsetPtr<void*>(Weapon, 0x1D90);
			//���󷢳���Ͷ����
			void* BowgunShlpPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x56E8);
			if (WeaponShlpPlot == nullptr || BowgunShlpPlot == nullptr)
				return false;

			void* ShlpPlot = nullptr;
			switch (From)
			{
			case 0:
				ShlpPlot = WeaponShlpPlot;
				break;
			case 1:
				ShlpPlot = BowgunShlpPlot;
				break;
			default:
				return false;
			}

			void* ShlpRoute = MH::Shlp::GetShlp(ShlpPlot, Id);
			if (ShlpRoute == nullptr)
				return false;
			ShlpRoute = *offsetPtr<void*>(ShlpRoute, 0x8);
			MH::Shlp::CallShlp(ShlpRoute, BasicGameData::PlayerPlot, BasicGameData::PlayerPlot, Coordinate);
			return true;
		}
		//����Ͷ����·������
		static void GenerateProjectilesCoordinateData(float*& CalculationCoordinates,Vector3 startPoint, Vector3 endPoint) {
			//����ָ��
			float* temp_float = CalculationCoordinates;
			//д����ʼ����
			*temp_float = startPoint.x;
			temp_float++;
			*temp_float = startPoint.y;
			temp_float++;
			*temp_float = startPoint.z;
			temp_float++;
			//��ʼ����д����ɣ���4���ֽ�
			*temp_float = 0;
			temp_float++;
			//����ָ��Ϊ���ֽڲ�д��1
			unsigned char* temp_byte = (unsigned char*)temp_float;
			*temp_byte = 1;

			//���軺��ָ���������ַ40��
			temp_float = offsetPtr<float>(CalculationCoordinates, 0x40);
			//д���������
			*temp_float = endPoint.x;
			temp_float++;
			*temp_float = endPoint.y;
			temp_float++;
			*temp_float = endPoint.z;
			temp_float++;
			//��������д����ɣ���4���ֽ�
			*temp_float = 0;
			temp_float++;
			//����ָ��Ϊ���ֽڲ�д��1
			temp_byte = (unsigned char*)temp_float;
			*temp_byte = 1;

			//���軺��ָ���������ַA0��
			int* tempCoordinateTailData = offsetPtr<int>(CalculationCoordinates, 0xA0);
			//д����������β����Ϣ
			*tempCoordinateTailData = 0x12;
			tempCoordinateTailData++;
			longlong* tempCoordinateTailData_longlong = (longlong*)tempCoordinateTailData;
			*tempCoordinateTailData_longlong = -1;
		}
		//����Ͷ����
		static bool CreateProjectiles(int Id, Vector3 startPoint, Vector3 endPoint, int From = 0) {
			//����Ͷ����·�����ݻ���ָ��
			float* CoordinatesData = new float[73];
			//��仺��������
			memset(CoordinatesData, 0, 73 * 4);
			//����Ͷ����·������
			GenerateProjectilesCoordinateData(CoordinatesData, startPoint, endPoint);
			//ִ������Ͷ����
			bool GenerateResults = CallProjectilesGenerate(Id, CoordinatesData, From);
			//��������
			delete[]CoordinatesData;
			return GenerateResults;
		}
	}
#pragma endregion

	//��ʼ��
	static bool Init() {
		if (!ModConfig::GameDataInit) {
			void* PlayerPlot = *(undefined**)MH::Player::PlayerBasePlot;
			void* PlayerInfoPlot = *(undefined**)MH::Player::BasePtr;
			BasicGameData::PlayerPlot = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
			BasicGameData::PlayerInfoPlot = *offsetPtr<undefined**>((undefined(*)())PlayerInfoPlot, 0xA8);
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
						Base::Monster::Monsters[monster] = Base::Monster::MonsterData(
							monster, 0, 0, 0, id, subId
						);
						return ret;
					});
				HookLambda(MH::Monster::dtor,
					[](auto monster) {
						Base::Monster::Monsters.erase(monster);
						return original(monster);
					});
				//�ӽ���������޸�
				HookLambda(MH::Player::Visual,
					[]() {
						GetVisualPtr(&Base::PlayerData::Coordinate::TempData::t_visual);
						if (Base::PlayerData::Coordinate::TempData::t_visual != nullptr) {
							Base::PlayerData::Coordinate::Visual.x = *offsetPtr<float>(Base::PlayerData::Coordinate::TempData::t_visual, 0x0);
							Base::PlayerData::Coordinate::Visual.y = *offsetPtr<float>(Base::PlayerData::Coordinate::TempData::t_visual, 0x4);
							Base::PlayerData::Coordinate::Visual.z = *offsetPtr<float>(Base::PlayerData::Coordinate::TempData::t_visual, 0x8);
							if (Base::PlayerData::Coordinate::TempData::t_SetVisual) {
								*offsetPtr<float>(Base::PlayerData::Coordinate::TempData::t_visual, 0x0) = Base::PlayerData::Coordinate::TempData::t_SetVisualCoordinate.x;
								*offsetPtr<float>(Base::PlayerData::Coordinate::TempData::t_visual, 0x4) = Base::PlayerData::Coordinate::TempData::t_SetVisualCoordinate.y;
								*offsetPtr<float>(Base::PlayerData::Coordinate::TempData::t_visual, 0x8) = Base::PlayerData::Coordinate::TempData::t_SetVisualCoordinate.z;
							}
						}
						return original();
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
				//����������
				PlayerData::Coordinate::TempData::t_SetVisualBind = nullptr;
				PlayerData::Coordinate::TempData::t_SetVisual = false;
				PlayerData::Coordinate::TempData::t_LockVisual = false;
				//����ί��
				Commission::CleanCommission();
				//�������ɸѡ��
				Monster::Filter = pair<int, int>(255, 255);
				//������һ��еĹ����ַ
				PlayerData::AttackMonsterPlot = nullptr;
				//�������Fsm
				PlayerData::Fsm = PlayerData::FsmData(0, 0);
				PlayerData::TempData::t_ManualFsmAction = PlayerData::FsmData(0, 0);
				PlayerData::TempData::t_executingFsmAction = false;
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
			PlayerData::Updata();
			//���»�����������
			vector<void*>::iterator it;
			for (it = World::EnvironmentalData::TempData::t_environmentalMessages.begin(); it != World::EnvironmentalData::TempData::t_environmentalMessages.end(); it++)
			{
				if (*it != nullptr) {
					if (Base::World::EnvironmentalData::Environmentals.find(*it) == Base::World::EnvironmentalData::Environmentals.end()) {
						Base::World::EnvironmentalData::Environmentals[*it] = 
						Base::World::EnvironmentalData::EnvironmentalData(
							*it,
							0,
							0, 
							0,
							*offsetPtr<int>(*it, 0x1AF0),
							*offsetPtr<int>(*it, 0x1AF4)
						);
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
			//��������ʱ��
			if (!Chronoscope::CheckChronoscope("SetVisual")) {
				if(!PlayerData::Coordinate::TempData::t_LockVisual)
					PlayerData::Coordinate::TempData::t_SetVisual = false;
				Chronoscope::DelChronoscope("SetVisual");
			}
			//������������
			if (!PlayerData::Coordinate::TempData::t_SetVisual) {
				PlayerData::Coordinate::TempData::t_SetVisualBind = nullptr;
			}
			//�������������
			if (PlayerData::Coordinate::TempData::t_SetVisualBind != nullptr) {
				PlayerData::Coordinate::TempData::t_SetVisualCoordinate.x = *offsetPtr<float>(PlayerData::Coordinate::TempData::t_SetVisualBind, 0x160);
				PlayerData::Coordinate::TempData::t_SetVisualCoordinate.y = *offsetPtr<float>(PlayerData::Coordinate::TempData::t_SetVisualBind, 0x164);
				PlayerData::Coordinate::TempData::t_SetVisualCoordinate.z = *offsetPtr<float>(PlayerData::Coordinate::TempData::t_SetVisualBind, 0x168);
			}
			//����ί��
			Commission::Run();
		}
	}
}