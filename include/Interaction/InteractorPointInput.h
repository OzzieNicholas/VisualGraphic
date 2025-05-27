/*
 * InteractorPointInput.h���û������뽻����
 *
 * ���ܸ�����
 *  - ͨ��������ɼ��û�����Ŀռ��
 *  - ֧��ʵʱ���ӻ��������縨������Ԥ����
 *  - ֧�� ESC �����ǰ���������
 *  - �ṩ�ӿڹ�����ģ�飨���㷨���������������������
 *
 * ʹ�ó�����
 *  - ���ڻ������ߡ�Bezier ���Ƶ㡢NURBS �������������/��������
 *  - ��Ϊ���ι��졢�����㷨���Ե�ǰ��������Դ
 *  - ���� PointEdit / ObjectPick �Ƚ���������ʹ��
 */

#pragma once

#include "./InteractorBase.h"
#include <vector>
#include <QVector3D>

class InteractorPointInput : public InteractorBase {
public:
    InteractorPointInput();
    ~InteractorPointInput() override;

    // ========== �������¼� ========== //
    void onMousePress(QMouseEvent* event, InteractorHost* host) override;
    void onMouseMove(QMouseEvent* event, InteractorHost* host) override;
    void onWheel(QWheelEvent* event, InteractorHost* host) override;
    void onKeyPress(QKeyEvent* event, InteractorHost* host) override;

    // ========== �����Ĵ��� ========== //

    // ��ȡ�����
    const std::vector<QVector3D>& getInputPoints() const;

    // ��������
    void clearInputPoints();

private:
    std::vector<QVector3D> m_inputPoints; // ����㼯
};
