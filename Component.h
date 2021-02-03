#pragma once

using namespace std;
using namespace loader;

namespace Component {
	struct Coordinate {
		float x, y, z;
		Coordinate(float x = 0, float y = 0, float z = 0) :x(x), y(y), z(z) {
		};
	};
	struct Effect {
		bool Enable = false;
		int group = 0;
		int record = 0;
	};
	
	/*
		��Ŀ���ƶ��������
		��������ҡ����������������ɼ������ʵ��
		ע��
			�ٶ�ֵԽ���ٶ�Խ��
			��Һ͹����Ƽ�ʹ��MovePlayerToPoint��MoveMonsterToPoint���в���
	*/
	static void MoveTargetToPoint(void* Target, Coordinate Point,bool Instant = true,float speed = 100.0) {
		if (Target == nullptr)
			return;
		if (Instant) {
			*offsetPtr<float>(Target, 0x160) = Point.x;
			*offsetPtr<float>(Target, 0x164) = Point.y;
			*offsetPtr<float>(Target, 0x168) = Point.z;
		}
		else {
			Base::Commission::MoveEntity::CommissionList[Target] = Base::Commission::MoveEntity::Parameter{
				Base::Vector3{ Point.x, Point.y, Point.z },
				nullptr,
				speed 
			};
		}
	}
	/*
		��Ŀ���ƶ���Ŀ��
		��������ҡ����������������ɼ������ʵ��
		ע��
			�ٶ�ֵԽ���ٶ�Խ��
			��Һ͹����Ƽ�ʹ��MovePlayerToTarget��MoveMonsterToTarget���в���
	*/
	static void MoveTargetToTarget(void* Target, void* ToTarget, bool Instant = true, float speed = 100.0) {
		if (Target == nullptr || ToTarget == nullptr)
			return;
		float TargetPointX = *offsetPtr<float>(Target, 0x160);
		float TargetPointY = *offsetPtr<float>(Target, 0x164);
		float TargetPointZ = *offsetPtr<float>(Target, 0x168);
		if (Instant) {
			*offsetPtr<float>(Target, 0x160) = TargetPointX;
			*offsetPtr<float>(Target, 0x164) = TargetPointY;
			*offsetPtr<float>(Target, 0x168) = TargetPointZ;
		}
		else {
			Base::Commission::MoveEntity::CommissionList[Target] = Base::Commission::MoveEntity::Parameter{
				Base::Vector3{ TargetPointX, TargetPointY, TargetPointZ },
				ToTarget,
				speed
			};
		}
	}
	/*
		������ƶ���Ŀ��
		ע��
			�ٶ�ֵԽ���ٶ�Խ��
	*/
	static void MovePlayerToPoint(Coordinate Point, Effect effect, bool Instant = true, float speed = 100.0) {
		if (effect.Enable) {
			Base::PlayerData::Effects::GenerateSpecialEffects(effect.group, effect.record);
		}

		if (Instant) {
			Base::PlayerData::Coordinate::TransportCoordinate(Point.x,Point.y,Point.z);
		}
		else {
			MoveTargetToPoint(Base::BasicGameData::PlayerPlot, Point, false, speed);
		}
	}
}