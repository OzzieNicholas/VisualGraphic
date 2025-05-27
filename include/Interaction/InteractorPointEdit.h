/*
 * InteractorPointEdit.h���û���༭������
 *
 * ���ܸ�����
 *  - ֧�ֶ�һ��ռ����н���ʽѡ�����ƶ�
 *  - �����ѡ�㡢��ס�϶��޸ĵ�λ��
 *  - ֧�� ESC ȡ����ǰѡ��״̬
 *  - �ṩ�����õ�ʰȡ�ݲ���ص�λ��
 *
 * ʹ�ó�����
 *  - �༭ NURBS��Bezier ���Ƶ�
 *  - �㷨�����ж�̬������ʼ����
 *  - ��ѧ��ʾ��ֱ�ۿ��ӵ��޸Ĺ���Ԫ��
 */

#pragma once

#include "./InteractorBase.h"
#include <vector>
#include <QVector3D>
#include <QPoint>

class InteractorPointEdit : public InteractorBase {
public:
    InteractorPointEdit();
    ~InteractorPointEdit() override;

    // ========== �������¼� ========== //
    void onMousePress(QMouseEvent* event, InteractorHost* host) override;
    void onMouseMove(QMouseEvent* event, InteractorHost* host) override;
    void onWheel(QWheelEvent* event, InteractorHost* host) override;
    void onKeyPress(QKeyEvent* event, InteractorHost* host) override;

	// ========== ��༭���� ========== //

    // ���ô��༭�ĵ�����
    void setTargetPoints(std::vector<QVector3D>* points);

    // ����ʰȡ�뾶����Ļ���أ�
    void setPickRadius(float radius);

private:
    std::vector<QVector3D>* m_pointsRef = nullptr; // �༭Ŀ�꣨�ⲿ���ݣ�
    int m_selectedIndex = -1;                      // ��ǰѡ�е�
    float m_pickRadius = 8.0f;                     // ʰȡ�ݲ�
    QPoint m_lastMousePos;                         // �ϴ����λ��
};
