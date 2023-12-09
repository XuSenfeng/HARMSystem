#include "platform_manage.h"
extern manager_t manager;
//��ȡ��¼��Ϣ
void platform_get_manage_login_data(int8_t *message)
{
    sprintf(message, "�𾴵� %s ����/Ůʿ ��ӭʹ��\r\n", manager.login.name);
}

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
            message, k, patient->login.id, patient->login.name, 
            status=='0'?str1:(status=='1'?str2:str3));
            if(status!='0')
            {
                doctor = platform_get_doc(patient->doc_id);
                if(doctor!=-1)
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
        if(service1 != -1){
            service2 = platform_get_service(doc_msg[2]);
            if(service2 != -1){
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

//������û���ƽ̨�ӿ�,�����������Ϣ
void platform_manage_commend(int8_t commend,int8_t *message, void *parameter)
{
    int8_t (*doc_msg)[31];
    int32_t *p;
    doctor_t *doctor;
    switch (commend)
    {
    case 1:
        //��ȡ��¼��Ϣ
        platform_get_manage_login_data(message);
        break;
    case 2:
    
        *(int *)parameter = listCURRENT_LIST_LENGTH(&manager.patient_LM);
        break;
    case 3:
        p = parameter;
        platform_manage_getpat_data(message, *p, *(p+1));
        break;
    case 4:
        //��ȡһ��ҽ������Ϣ
        doctor = platform_get_doc(parameter);
        if(doctor!=-1)
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
        doctor = platform_get_doc(parameter);
        if(doctor!=-1)
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

        doc_msg = parameter;
        doctor = platform_get_doc(doc_msg[0]);
        //printf("����");while(1);
        if(doctor!=-1)
        {
            
            platform_manage_chg_doc(doctor, message, parameter);
        }else{
            sprintf(message, "û����һ��ҽ��\r\n");
        }
        break;
    case 7:
        platform_department_init(parameter);
        sprintf(message, "��ӳɹ�\r\n");
    default:
        break;
    }
}