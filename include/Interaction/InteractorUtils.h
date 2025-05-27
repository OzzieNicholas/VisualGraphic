/*
 * InteractorUtils.h�����������������߼�
 *
 * ���ܸ�����
 *  - �ṩ���õĵ����ӳ�䡢����ת���Ȳ���
 *  - ������ģ�鹲���ߺ������������ؼ�����
 *
 * ʹ�ó�����
 *  - InteractorXxx �н��е���� �� ��������ת��
 *  - ���ڻ��Ƹ��������塢ʰȡ��ͶӰ����������У׼��
 *  - �� InteractorHost ���ʹ�ã��ṩͨ�ý����任֧��
 */

#pragma once

#include <QVector3D>
#include <QMatrix4x4>
#include <QSize>
#include <limits>

namespace InteractorUtils {
    // ���ת��Ϊƽ����������
    QVector3D mapClickToPlane(
        float screenX,
        float screenY,
        const QMatrix4x4& projection,
        const QMatrix4x4& view,
        const QSize& viewportSize
    );
}
