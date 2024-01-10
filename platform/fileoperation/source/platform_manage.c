/**
  ******************************************************************************
  * @file    platform_manage.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   ����ļ������ݿ��API��,��Ҫ��Ϊ��ʵ�ֹ���Ա������API����
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


#include "platform_manage.h"
extern manager_t manager;
/**
  * @brief  ��ȡ��¼��Ϣ
  * @param  message:���ص���ʾ��Ϣ
  * @retval ��
  */
void platform_get_manage_login_data(int8_t *message)
{
    sprintf(message, "\0");
    sprintf(message, "�𾴵� %s ����/Ůʿ ��ӭʹ��\r\n", manager.login.name);
    //printf(message);
    //printf("4444444444");
}
/**
  * @brief  ��ȡ���˵���Ϣ
  * @param  message:���ص���ʾ��Ϣ
  * @param  begin:��ʼλ��
  * @param  num:��ȡ������
  * @retval ��
  */
void platform_manage_getpat_data(int8_t *message, int32_t begin, int32_t num){

    patient_t *patient;
    doctor_t *doctor;
    int32_t i, k=0, j, t;
    int8_t status;
    ListItem_t *list_test;
    int8_t str1[] = "û��ԤԼ";
    int8_t str2[] = "ԤԼ��û������";
    int8_t str3[] = "�ȴ�����";
    //��ջ�����
    sprintf(message, "\0");

    list_test = listGET_HEAD_ENTRY(&manager.patient_LM);
    //��������Աʹ�õĲ���
    list_test = listGET_NEXT(list_test);
    patient = listGET_LIST_ITEM_OWNER(list_test);
    for(i=0;i<manager.patient_LM.uxNumberOfItems;i++)
    {
        status = patient->doctor_L.xItemValue;
        if(k>=begin && k<begin + num){
            sprintf(message, "%s���� %d �ŵ�id��: %s ����: %s ��ǰ��״̬�� %s\r\n", 
            message, k+1, patient->login.id, patient->login.name, 
            status==0?str1:(status==1?str2:str3));
            if(status!=0)
            {
                doctor = platform_get_doc(patient->doc_id);
                if(doctor!=ERROR)
                {
                    sprintf(message, "%s��ǰ����ҽ���� %s %s\r\n", 
                    message, doctor->login.name, doctor->login.id);
                }
            }
        }
        k++;
        list_test = listGET_NEXT(list_test);
        patient = listGET_LIST_ITEM_OWNER(list_test);

    }

}
/**
  * @brief  �ı�һ��ҽ������Ϣ
  * @param  doctor:Ҫ�޸ĵ�ҽ��
  * @param  message:���ص���ʾ��Ϣ
  * @param  parameter:��ȡ���Ĳ��� int8_t (*doc_msg)[31]���� 1ѡ�� 2�޸��Ժ��ֵ
  * @retval ��
  */
void platform_manage_chg_doc(doctor_t *doctor,int8_t* message, int8_t (*doc_msg)[31]){
    outpatient_service_t *service1, *service2;
    if(doc_msg[1][0]=='1')
    {
        //������
        sprintf(message, "���� %s ��Ϊ %s\r\n", doctor->login.name, doc_msg[2]);
        strcpy(doctor->login.name, doc_msg[2]);
        
    }else if(doc_msg[1][0]=='2')
    {
        //��ְ��
        sprintf(message, "ְ�� %s ��Ϊ %s\r\n", doctor->level, doc_msg[2]);
        strcpy(doctor->level, doc_msg[2]);
        //����ְ�����ù�ְ
        if(strcmp(doc_msg[2], DOC_LEVE_1)==0)
        {
            doctor->manage_L.xItemValue = 1;
        }
        if(strcmp(doc_msg[2], DOC_LEVE_2)==0)
        {
            doctor->manage_L.xItemValue = 2;
        }
        if(strcmp(doc_msg[2], DOC_LEVE_3)==0)
        {
            doctor->manage_L.xItemValue = 3;
        }
        if(strcmp(doc_msg[2], DOC_LEVE_4)==0)
        {
            doctor->manage_L.xItemValue = 4;
        }
        if(strcmp(doc_msg[2], DOC_LEVE_5)==0)
        {
            doctor->manage_L.xItemValue = 5;
        }
        uxListRemove(&doctor->manage_L);
        vListInsert(&manager.doctors_LM, &doctor->manage_L);
    }else if(doc_msg[1][0]=='3'){
        //��¼����
        sprintf(message, "���� %s ��Ϊ %s\r\n", doctor->login.passwd, doc_msg[2]);
        strcpy(doctor->login.passwd, doc_msg[2]);
    }else if(doc_msg[1][0]=='4'){
        //����
        service1 = platform_get_service(doctor->service);
        if(service1 != ERROR){
            service2 = platform_get_service(doc_msg[2]);
            if(service2 != ERROR){
                strcpy(doctor->service, doc_msg[2]);
                uxListRemove(&doctor->service_L);
                vListInsertEnd(&service2->doctors_LM, &doctor->service_L);
                sprintf(message, "���³ɹ�\r\n");
            }else{
                sprintf(message, "ҽ���µĲ���û�ҵ�,�����и���\r\n");
            }
        }else{
            sprintf(message, "ҽ�������Ĳ���û�ҵ�, �Ƚ��и���\r\n");
        }
    }
}
/**
  * @brief  �ı�һ�����˵���Ϣ
  * @param  patient:Ҫ�޸ĵĲ���
  * @param  message:���ص���ʾ��Ϣ
  * @param  parameter:��ȡ���Ĳ��� int8_t (*pat_msg)[31]���� 1ѡ�� 2�޸��Ժ��ֵ
  * @retval ��
  */
void platform_manage_chg_pat(patient_t *patient,int8_t* message, int8_t (*pat_msg)[31]){

    if(pat_msg[1][0]=='1')
    {
        //������
        sprintf(message, "���� %s ��Ϊ %s\r\n", patient->login.name, pat_msg[2]);
        strcpy(patient->login.name, pat_msg[2]);
        
    }else if(pat_msg[1][0]=='2'){
        //��¼����
        sprintf(message, "���� %s ��Ϊ %s\r\n", patient->login.passwd, pat_msg[2]);
        strcpy(patient->login.passwd, pat_msg[2]);
    }
}
/**
  * @brief  ���һ��ҽ��
  * @param  message:���ص���ʾ��Ϣ
  * @param  parameter:��ȡ���Ĳ��� int8_t (*doc_msg)[31]����, 0���� 1ְλ 2ְ�� 3���� 4����ʱ�� 5-0�Ӵ�����
  * @retval ��
  */
void platform_manage_add_doc(int8_t *message, int8_t *parameter)
{
    int8_t (*doc_msg)[31] =parameter ;
    int8_t doc_id[21];
    time_t timep;
    struct tm *p;
    doctor_t *doctor;
    time(&timep);
    p=gmtime(&timep);
    sprintf(doc_id, "%04d%02d%02d%04d",1900+p->tm_year, 1+p->tm_mon, p->tm_mday, manager.doctors_LM.uxNumberOfItems);
    //printf("���� %s %s %s\r\n", doc_id, doc_msg[1], doc_msg[2]);while(1);
    doctor = platform_add_doctor(doc_msg[0], doc_id, doc_msg[3], doc_msg[1], doc_msg[2], doc_msg[5][0], doc_msg[4], 0, doc_msg[5][1]);
    if(doctor != ERROR)
    {
        sprintf(message, "��ӳɹ�\r\n");
        
    }else{
        sprintf(message, "���ʧ��,������Ϣ����\r\n");
    }

}

void platform_manage_get_msg(int8_t *message, int parameter)
{
    doctor_t *doctor;
    ListItem_t *list_test, *list_test3, *list_test2;
    int32_t i, j, t, max, num;
    one_department_t *department;
    outpatient_service_t *service;
    //�����Ϣ
    sprintf(message, "\0");
    
    
    if(parameter == 1 ){
        //������ȡ�Ӵ�����������ҽ������Ϣ
        list_test = listGET_HEAD_ENTRY(&manager.doctors_LM);
        doctor = listGET_LIST_ITEM_OWNER(list_test);
        max = doctor->num_had_accept;
        for(i=0;i<manager.doctors_LM.uxNumberOfItems;i++)
        {
            if(doctor->num_had_accept>max)
                max = doctor->num_had_accept;
            list_test = listGET_NEXT(list_test);
            doctor = listGET_LIST_ITEM_OWNER(list_test);
        }
        list_test = listGET_NEXT(list_test);
        doctor = listGET_LIST_ITEM_OWNER(list_test);
        for(i=0;i<manager.doctors_LM.uxNumberOfItems;i++)
        {
            if(doctor->num_had_accept == max)
                sprintf(message, "%s%s����� %s ҽ��,Ŀǰ�Ӵ����� %d��\r\n", 
                message, doctor->service, 
                doctor->login.name, doctor->num_had_accept);
            list_test = listGET_NEXT(list_test);
            doctor = listGET_LIST_ITEM_OWNER(list_test);
        }
    }else if(parameter==2){
        max = 0;
        list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
        department = listGET_LIST_ITEM_OWNER(list_test);
        for(i=0;i<manager.departments_LM.uxNumberOfItems;i++)
        {
            //��ȡ��һ������
            num = 0;
            //���������������������
            list_test2 = listGET_HEAD_ENTRY(&department->services_LM);
            service = listGET_LIST_ITEM_OWNER(list_test2);
            for(j=0;j<department->services_LM.uxNumberOfItems;j++)
            {

                //��ȡ����ҽ��
                list_test3 = listGET_HEAD_ENTRY(&service->doctors_LM);
                doctor = listGET_LIST_ITEM_OWNER(list_test3);
                for(t=0;t<service->doctors_LM.uxNumberOfItems;t++)
                {
                    num += doctor->num_had_accept;
                    list_test3 = listGET_NEXT(list_test3);
                    doctor = listGET_LIST_ITEM_OWNER(list_test3);
                }

                list_test2 = listGET_NEXT(list_test2);
                service = listGET_LIST_ITEM_OWNER(list_test2);

                
            }
            

            if(max<num)
                max = num;
            list_test = listGET_NEXT(list_test);
            department = listGET_LIST_ITEM_OWNER(list_test);

        }
        list_test = listGET_HEAD_ENTRY(&manager.departments_LM);
        department = listGET_LIST_ITEM_OWNER(list_test);
        for(i=0;i<manager.departments_LM.uxNumberOfItems;i++)
        {
            //��ȡ��һ������
            num = 0;
            //���������������������
            list_test2 = listGET_HEAD_ENTRY(&department->services_LM);
            service = listGET_LIST_ITEM_OWNER(list_test2);
            for(j=0;j<department->services_LM.uxNumberOfItems;j++)
            {

                //��ȡ����ҽ��
                list_test3 = listGET_HEAD_ENTRY(&service->doctors_LM);
                doctor = listGET_LIST_ITEM_OWNER(list_test3);
                for(t=0;t<service->doctors_LM.uxNumberOfItems;t++)
                {
                    num += doctor->num_had_accept;
                    list_test3 = listGET_NEXT(list_test3);
                    doctor = listGET_LIST_ITEM_OWNER(list_test3);
                }

                list_test2 = listGET_NEXT(list_test2);
                service = listGET_LIST_ITEM_OWNER(list_test2);
                
            }
            

            if(max==num)
                sprintf(message, "%s%s���� Ϊ���ܻ�ӭ�Ĳ���,Ŀǰ�Ӵ����� %d��\r\n", 
                message, department->name, num);

            list_test = listGET_NEXT(list_test);
            department = listGET_LIST_ITEM_OWNER(list_test);

        }
    }
}


/**
  * @brief  ����ǹ����ߵ�����ӿ�,�����������Ϣ
  * @param  commend:��ȡ��������
  * @param  message:���ص���ʾ��Ϣ
  * @param  parameter:һ������
  * @retval ��
  */
void platform_manage_commend(int8_t commend,int8_t *message, void *parameter)
{
    int8_t (*doc_msg)[31];
    int32_t *p;
    doctor_t *doctor;
    patient_t *patient;
    switch (commend)
    {
    case 1:
        //��ȡ��¼��Ϣ
        platform_get_manage_login_data(message);
        break;
    case 2:
        //���ز��˵�����
        *(int *)parameter = listCURRENT_LIST_LENGTH(&manager.patient_LM);
        break;
    case 3:
        //��ȡĳһϵ�в��˵���Ϣ
        //������һ��int32_t������, ���ֵĵ�һ����������ʼλ��,�ڶ��������ǽ�����λ��
        p = parameter;
        platform_manage_getpat_data(message, *p, *(p+1));
        break;
    case 4:
        //��ȡһ��ҽ������Ϣ
        //������ҽ����id
        doctor = platform_get_doc(parameter);
        if(doctor != ERROR)
        {
            sprintf(message, "ҽ�� %s ��� %s ְ�� %s ���� %s\r\n",
            doctor->login.name, 
            doctor->login.id, 
            doctor->level, 
            doctor->service);
        }else{
            sprintf(message, "û����һ��ҽ��\r\n");
            *(int8_t *)parameter = 0;
        }
        break;
    case 5:
        //ɾ��һ��ҽ��
        //������ҽ����id
        doctor = platform_get_doc(parameter);
        if(doctor!= ERROR)
        {
            sprintf(message, "�Ѿ�ɾ��ҽ�� %s ��� %s ְ�� %s ���� %s\r\n",
            doctor->login.name, 
            doctor->login.id, 
            doctor->level, 
            doctor->service);
            platform_del_doctor(doctor);
        }else{
            sprintf(message, "û����һ��ҽ��\r\n");
        }
        break;
    case 6:
        //��ҽ������Ϣ�����޸�
        /*������ (*doc_msg)[31]
        ��һ���ַ�����ҽ����id
        �ڶ���������[0]λ�ñ�����Ҫ�ı�Ĳ���
        �����������Ǹı��Ժ�Ĳ���*/
        doc_msg = parameter;
        doctor = platform_get_doc(doc_msg[0]);
        //printf("����");while(1);
        if(doctor!=ERROR)
        {
            
            platform_manage_chg_doc(doctor, message, parameter);
        }else{
            sprintf(message, "û����һ��ҽ��\r\n");
        }
        break;
    case 7:
        //�����ǲ��ŵ������ַ���
        platform_department_init(parameter);
        sprintf(message, "��ӳɹ�\r\n");
        break;
    case 8:
        //���һ��ҽ��
        //��ȡ���Ĳ��� int8_t (*doc_msg)[31]����, 0���� 1ְλ 2ְ�� 3���� 4����ʱ�� 5-0�Ӵ�����
        platform_manage_add_doc(message, parameter);
        break;
    case 9:
        //��ȡһ��ҽ������Ϣ
        //������ҽ����id
        patient = platform_get_patient(parameter);
        if(patient != ERROR)
        {
            sprintf(message, "���� %s ��� %s\r\n",
            patient->login.name, 
            patient->login.id);
        }else{
            sprintf(message, "û����һ������\r\n");
            *(int8_t *)parameter = 0;
        }
        break;
    case 10:
        //ɾ��һ������
        //�����ǲ��˵�id
        patient = platform_get_patient(parameter);
        if(patient!=ERROR)
        {
            sprintf(message, "�Ѿ�ɾ������ %s ��� %s\r\n",
            patient->login.name, 
            patient->login.id);
            platform_del_patient(patient);
        }else{
            sprintf(message, "û����һ������\r\n");
        }
        break;
    case 11:
        //�Բ��˽����޸�
        /*������ (*p)[31]
        ��һ���ַ����ǲ��˵�id
        �ڶ���������[0]λ�ñ�����Ҫ�ı�Ĳ���
        �����������Ǹı��Ժ�Ĳ���*/
        doc_msg = parameter;
        patient = platform_get_patient(doc_msg[0]);
        //printf("����");while(1);
        if(patient!=ERROR)
        {
            
            platform_manage_chg_pat(patient, message, parameter);
        }else{
            sprintf(message, "û����һ������\r\n");
        }
        break;
    case 12:
        //��ȡһЩ��������Ϣ
        platform_manage_get_msg(message, parameter);
        break;
    default:
        break;
    }
}