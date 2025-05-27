/*
 * InteractorObjectSelect.h������ѡ�񽻻���
 *
 * ���ܸ�����
 *  - �û�ͨ�������ѡ�г����еĶ���
 *  - ���ڶ������ĵ�����λ�õ�ͶӰ�����ж�ѡ��
 *  - �ṩѡ��״̬��ѯ������Ƚӿ�
 *
 * ʹ�ó�����
 *  - HMI �ؼ�ѡ��ģ�����ѡ��
 *  - �������α༭�����������ʾ����ڽ���
 *  - �㷨����ʱ����ָ��Ŀ�����
 */

#pragma once

#include "./InteractorBase.h"
#include <vector>
#include <QVector3D>
#include <QPoint>

class InteractorObjectSelect : public InteractorBase {
public:
    InteractorObjectSelect();
    ~InteractorObjectSelect() override;

    // ========== �������¼� ========== //
    void onMousePress(QMouseEvent* event, InteractorHost* host) override;
    void onMouseMove(QMouseEvent* event, InteractorHost* host) override;
    void onWheel(QWheelEvent* event, InteractorHost* host) override;
    void onKeyPress(QKeyEvent* event, InteractorHost* host) override;

	// ========== ѡ����� ========== //

    // ���ÿ�ѡ�����Ŀռ�λ��
    void setSelectableCenters(const std::vector<QVector3D>* centers);

    // ����ʰȡ�ݲ�
    void setPickRadius(float radius);

    // ��ȡ��ǰѡ�ж���������-1 ��ʾ��ѡ�У�
    int getSelectedIndex() const;

    // �����ǰѡ��״̬
    void clearSelection();

private:
    const std::vector<QVector3D>* m_centersRef = nullptr; // ѡ��Ŀ�����ĵ�
    float m_pickRadius = 8.0f; // ʰȡ�ݲ�
    int m_selectedIndex = -1; // ��ǰѡ������
};
