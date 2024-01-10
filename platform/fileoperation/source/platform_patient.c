/**
  ******************************************************************************
  * @file    platform_patient.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   ����ļ������ݿ��API��,��Ҫ��Ϊ��ʵ�ֲ��˵�����API����
  * @author  XvSenfeng(������)
  ******************************************************************************
  * @attention
  * ��������XvSenfeng��������ѿ�Դ����
  * ���������鿴��ʹ�ú��޸ģ���Ӧ�õ��Լ�����Ŀ֮��
  * �����Ȩ��XvSenfeng���У��κ��˻���֯���ý����Ϊ����
  * ����㷢�ֳ����е�©�����߱��󣬿�ͨ���ʼ������Ƿ�����1458612070@qq.com
  * �����ʼ�֮ǰ��������ȵ����¶�̬ҳ��鿴���³�������������Ѿ��޸ģ��������ٷ��ʼ�
  * https://github.com/XuSenfeng
  ******************************************************************************
  */ 


#include "platform_patient.h"
extern manager_t manager;

void platform_patient_getdoc_data_d(int8_t *message, int32_t begin, int32_t num){
    one_department_t *department;
    outpatient_service_t *service;
    doctor_t *doctor;
    int32_t i, k=0, j, t;
    ListItem_t *list_test, *list_test2, *list_test3;
    //��ջ�����
    sprintf(message, "\0");
    list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
    department = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.departments_LM.uxNumberOfItems;i++)
    {
        //��ȡ��һ������
        if(k>=begin && k<begin + num)
            sprintf(message, "%s\r\n���� %s ������ %d ������\r\n", message, department->name, department->services_LM.uxNumberOfItems);
        //���������������������
        list_test2 = listGET_HEAD_ENTRY(&department->services_LM);
        service = listGET_LIST_ITEM_OWNER(list_test2);
        for(j=0;j<department->services_LM.uxNumberOfItems;j++)
        {
            if(k>=begin && k<begin + num)
                sprintf(message, "%s\t����%d��: %s\r\n", message, j+1, service->name);
            
            //��ȡ����ҽ��
            list_test3 = listGET_HEAD_ENTRY(&service->doctors_LM);
            doctor = listGET_LIST_ITEM_OWNER(list_test3);
            for(t=0;t<service->doctors_LM.uxNumberOfItems;t++)
            {
                if(k>=begin && k<begin + num)
                    sprintf(message, "%s\t\tҽ�� %s ��id�� %s  %s\r\n", message, doctor->login.name, doctor->login.id, doctor->level);
                list_test3 = listGET_NEXT(list_test3);
                doctor = listGET_LIST_ITEM_OWNER(list_test3);
            }

            list_test2 = listGET_NEXT(list_test2);
            service = listGET_LIST_ITEM_OWNER(list_test2);

            
        }
        k++;
        //��ӡ����������
        if(k>=begin + num)
            break;
        list_test = listGET_NEXT(list_test);
        department = listGET_LIST_ITEM_OWNER(list_test);

    }

}
/**
  * @brief  ����ְ�ƻ�ȡҽ������Ϣ
  * @param  message: Ҫ���ص���Ϣ
  * @param  begin: ��ʼ��λ��
  * @param  end: ������λ��
  * @retval ��
  */
void platform_patient_getdoc_data_L(int8_t *message, int32_t begin, int32_t num){

    doctor_t *doctor;
    outpatient_service_t *service;
    int32_t i, k=0, j, t;
    ListItem_t *list_test, *list_test2, *list_test3;
    //��ջ�����
    sprintf(message, "\0");
    //��ȡ��һ��ҽ��
    list_test = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.doctors_LM.uxNumberOfItems;i++)
    {
        
        if(k>=begin && k<begin + num)
            sprintf(message, "%s%s %s ҽ��ְλ�� %s ԤԼid�� %s �����ԽӴ�%d����\r\n", 
            message, doctor->level,
            doctor->login.name, doctor->service, 
            doctor->login.id, doctor->num_to_accept - doctor->patient_LM.uxNumberOfItems);
        k++;
        if(k>=begin + num)
            break;
        list_test = listGET_NEXT(list_test);
        doctor = listGET_LIST_ITEM_OWNER(list_test);

    }

}
/**
  * @brief  ��ȡĳһ��ҽ���Ĺ���ʱ��
  * @param  message: Ҫ���ص���Ϣ
  * @param  parameter: ҽ����id
  * @retval ��
  */
void platform_patient_get_doc_time(int8_t *message,int8_t *parameter)
{
    int8_t weekday[7][14] = {
    "������",
    "����һ",
    "���ڶ�",
    "������",
    "������",
    "������",
    "������",
    };
    doctor_t *doctor;
    sprintf(message, "\0");
    doctor = platform_get_doc(parameter);
    int32_t i;
    if(doctor != ERROR)
    {
        sprintf(message, "|ʱ��\t|����\t|����\t|\r\n");
        sprintf(message, "%s-----------------------\r\n", message);
        for(i=0;i<7;i++)
        {
            //���ݻ�ȡ������Ϣ���д�ӡ,�Ա�����ʽ�������
            sprintf(message, "%s|%s\t|%s\t|%s\t|\r\n", message, weekday[i], doctor->workday[i]=='1'?"��":"X",  doctor->workday[i+1]=='1'?"��":"X");
        }
    }else{
        printf(message, "û���ҵ���һ��ҽ��\r\n");
    }
}
/**
  * @brief  ��ȡĳһ��ҽ������ϸ��Ϣ
  * @param  message: Ҫ���ص���Ϣ
  * @param  parameter: ҽ����id
  * @retval ��
  */
void platform_patient_get_doc_msg(int8_t *message,int8_t *parameter)
{
    doctor_t *doctor = platform_get_doc(parameter);
    if(doctor == ERROR)
    {
        sprintf(message, "û���ҵ���λҽ��\r\n");
        return;
    }
    //���Ȼ�ȡҽ���Ĺ���ʱ��
    platform_patient_get_doc_time(message, parameter);
    sprintf(message, "%sҽ�������� %s ���ڵĲ��� %s �����ԽӴ� %d ������\r\n", 
    message, doctor->login.name, 
    doctor->service, 
    doctor->num_to_accept - doctor->patient_LM.uxNumberOfItems);
}

/**
  * @brief  ��ȡĳһ��ʱ��ε�ҽ��������
  * @param  parameter: Ҫ��ȡ��ʱ��,ʵ�ʵ�32λ������, ��һ�������洢�������ڼ�,�ڶ��������洢�������绹������,ͨ���������������з���
  * @retval ��
  */
void platform_patient_get_doc_tim_num(int32_t *parameter)
{
    doctor_t *doctor;
    outpatient_service_t *service;
    int32_t i, k=0, day;
    ListItem_t *list_test, *list_test2, *list_test3;
    if(parameter[0]>6 || parameter[0]<0 || parameter[1] <0 || parameter[1] >2)
    {
        //�����ʱ�䲻����
        parameter[2]=0;
        return;
    }
    day = parameter[0]*2 + parameter[1]-1;
    //��ջ�����
    
    //��ȡ��һ��ҽ��
    list_test = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.doctors_LM.uxNumberOfItems;i++)
    {
        if(doctor->workday[day]== '1')
        {
            k++;
        }
        list_test = listGET_NEXT(list_test);
        doctor = listGET_LIST_ITEM_OWNER(list_test);
    }
    parameter[2] = k;
}


/**
  * @brief  ��ȡĳһ��ҽ������Ϣͨ�����Ĺ���ʱ��
  * @param  message: Ҫ���ص���ʾ��Ϣ
  * @param  begin: ��ʼ����Ϣ����
  * @param  num: Ҫ���ص���Ϣ������
  * @param  day: Ҫ���ص�ʱ���ǵڼ���
  * @retval ��
  */
void platform_patient_getdoc_data_T(int8_t *message, int32_t begin, int32_t num, int32_t day)
{
    doctor_t *doctor;
    outpatient_service_t *service;
    int32_t i, k=0;
    ListItem_t *list_test, *list_test2, *list_test3;
    //��ջ�����
    sprintf(message, "\0");

    //��ȡ��һ��ҽ��
    list_test = listGET_HEAD_ENTRY(&manager.doctors_LM);
    doctor = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.doctors_LM.uxNumberOfItems;i++)
    {
        if(doctor->workday[day]== '1'){
            if(k>=begin && k<begin + num)
                sprintf(message, "%s%s %s ҽ��ְλ�� %s ԤԼid�� %s �����ԽӴ�%d����\r\n", 
                message, doctor->level,
                doctor->login.name, doctor->service, 
                doctor->login.id, doctor->num_to_accept - doctor->patient_LM.uxNumberOfItems);
            k++;
            if(k>=begin + num)
                break;
        }
        list_test = listGET_NEXT(list_test);
        doctor = listGET_LIST_ITEM_OWNER(list_test);

    }
}

/**
  * @brief  ������û���ƽ̨�ӿ�,�����������Ϣ
  * @param  commend:Ҫ���������
  * @param  id:��¼�Ĳ���id
  * @param  message: Ҫ���ص���Ϣ
  * @param  parameter: �������Ĳ���
  * @retval ��
  */
void platform_patient_commend(int8_t commend, char *id, char *message, void *parameter)
{
    patient_t *patient;
    int32_t ret;
    patient = platform_get_patient(id);
    int32_t *p;
    int8_t (*p_8)[30];
    int8_t id_n[21];
    time_t timep;
    struct tm *p_tm;
    if(patient != ERROR || strlen(id)==0)
    {
        switch (commend)
        {
        case 1:
            //��ȡ��¼��Ϣ
            //����Ҫ����
            platform_get_patient_login_data(patient, message);
            break;
        case 2:
            //���ص�ǰ��ҽ��������
            p = parameter;
            *(p+1) = listCURRENT_LIST_LENGTH(&manager.doctors_LM);
            *p = listCURRENT_LIST_LENGTH(&manager.departments_LM);
            break;
        case 3:
            //����ĳһ��ҽ��,������ҽ����id
            ret  = platform_patient_appointment(patient, parameter);
            if(ret == 1)
            {
                sprintf(message, "���³ɹ�\r\n");
            }else
            {
                sprintf(message, "����ʧ��,�����������id,�Լ�ҽ���ĿɽӴ�����\r\n");
            }
            break;
        case 4:
            //��ȡ����ҽ������Ϣ, ������һ��int32_t������,��һ������ʼλ��,�ڶ����ǽ�������Ϣλ��
            p = parameter;
            platform_patient_getdoc_data_d(message, *p, *(p+1));
            break;
        case 5:
            //����һ������,��������parameter[3][30],��һ��������, �ڶ���������,֮�����id�������뵽����
            p_8 = parameter;
            sprintf(message, "");
            time(&timep);
            p_tm=gmtime(&timep);
            sprintf(id_n, "%04d%02d%02d%04d",1900+p_tm->tm_year, 1+p_tm->tm_mon, p_tm->tm_mday, manager.patient_LM.uxNumberOfItems);
            //printf("��%d ��%d ��%d\r\n", 1900+p_tm->tm_year, 1+p_tm->tm_mon, p_tm->tm_mday);
            patient = platform_add_patient(*p_8, id_n, *(p_8+1), '0', "0", " ��");
            if(patient==ERROR)
            {
                sprintf(message, "��ȡ�û�ʧ��,ԭ�������ɵ�id�ظ�,�����̨������\r\n");
            }else
            {
                sprintf(message, "\r\n�û� %s ����ɹ�, ����id�� %s �������Ϊ��¼ƾ֤\r\n", patient->login.name, patient->login.id);
                //�����û���Ϣ
                strcpy(id, patient->login.id);
                sprintf(message, "%s����ǰ�������� %s\r\n",message,  *(p_8+1));
            }
            break;
        case 6:
            //��ȡҽ������Ϣͨ��ְ��
            p = parameter;
            platform_patient_getdoc_data_L(message, *p, *(p+1));
            break;
        case 7:
            //��ȡҽ���Ĺ���ʱ�����Ϣ
            platform_patient_get_doc_time(message, parameter);
            break;
        case 8:
            //ɾ�����˵�ԤԼ
            ret  = platform_patient_appointment(patient, parameter);
            if(ret == 1)
            {
                sprintf(message, "ȡ��ԤԼ�ɹ�\r\n");
            }else
            {
                sprintf(message, "ȡ��ʧ��,���Ժ�����\r\n");
            }
            break;
        case 9:
            //��ȡҽ������ϸ��Ϣ
            platform_patient_get_doc_msg(message, parameter);
            break;
        case 10: 
            //��ȡĳ��ʱ��ε�ҽ��������
            platform_patient_get_doc_tim_num(parameter);
            break;
        case 11:
            //��ȡҽ������Ϣͨ��ʱ��
            p = parameter;
            platform_patient_getdoc_data_T(message, *p, *(p+1), *(p+2));
            break;
        default:
            break;
        }
    }else
    {
        sprintf(message, "��ȡ����ʧ��\r\n");
    }
}
/**
  * @brief  ��ȡ��¼��Ϣ
  * @param  patient:Ҫ����Ĳ���
  * @param  message:ҪҪ���ص���Ϣ�����λ��
  * @retval ��
  */
void platform_get_patient_login_data(patient_t *patient, int8_t *message)
{
    uint32_t status;
    doctor_t *doctor;
    
    status = platform_get_patient_status(patient);
    sprintf(message, "�𾴵� %s ����/Ůʿ\r\n", patient->login.name);
    if(status == WITHOUT_APPLICATION)
        sprintf(message, "%s����ǰ��ԤԼ״̬��û��ԤԼ\r\n", message);
    else if(status == FIRST_VISIT_DOCTOR)
        sprintf(message, "%s����ǰ��ԤԼ״̬��ԤԼû�г���\r\n", message);
    else if(status == SUBSQUENT_VISIT)
        sprintf(message, "%s����ǰ��ԤԼ״̬�ǵȴ�����\r\n", message);
    if(patient->doctor_L.xItemValue!=0)
    {
        doctor = platform_get_doc(patient->doc_id);
        sprintf(message, "%s����ǰ���� %s ����� %s ҽ��\r\n", message, doctor->service, doctor->login.name);
    }
    sprintf(message, "%s����ǰ����Ϣ: \r\n%s\r\n", message, patient->message);
}