/**
  ******************************************************************************
  * @file    list.c
  * @version V1.0
  * @date    2023-12-10
  * @brief   实现一个链表的操作
  * @author  XvSenfeng(焦浩洋)
  ******************************************************************************
  * @attention
  * 本程序由XvSenfeng创建并免费开源共享
  * 你可以任意查看、使用和修改，并应用到自己的项目之中
  * 程序版权归XvSenfeng所有，任何人或组织不得将其据为己有
  * 如果你发现程序中的漏洞或者笔误，可通过邮件向我们反馈：1458612070@qq.com
  * 发送邮件之前，你可以先到更新动态页面查看最新程序，如果此问题已经修改，则无需再发邮件
  * https://github.com/XuSenfeng
  ******************************************************************************
  */ 

#include "list.h"


/* 链表初始化 */
void vListInitialise( List_t * const pxList )
{
	/* 将链表索引指针指向最后一个节点 */
	pxList->pxIndex = ( ListItem_t * ) &( pxList->xListEnd );

	/* 将链表最后一个节点的辅助排序的值设置为最大，确保该节点就是链表的最后节点 */
	pxList->xListEnd.xItemValue = portMAX_DELAY;

    /* 将最后一个节点的pxNext和pxPrevious指针均指向节点自身，表示链表为空 */
	pxList->xListEnd.pxNext = ( ListItem_t * ) &( pxList->xListEnd );
	pxList->xListEnd.pxPrevious = ( ListItem_t * ) &( pxList->xListEnd );

	/* 初始化链表节点计数器的值为0，表示链表为空 */
	pxList->uxNumberOfItems = 0;
}

/* 节点初始化 */
void vListInitialiseItem( ListItem_t * const pxItem )
{
	/* 初始化该节点所在的链表为空，表示节点还没有插入任何链表 */
	pxItem->pvContainer = NULL;
}


/* 将节点插入到链表的尾部 */
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem )
{
	ListItem_t * const pxIndex = pxList->pxIndex;

	pxNewListItem->pxNext = pxIndex;
	pxNewListItem->pxPrevious = pxIndex->pxPrevious;
	pxIndex->pxPrevious->pxNext = pxNewListItem;
	pxIndex->pxPrevious = pxNewListItem;

	/* 记住该节点所在的链表 */
	pxNewListItem->pvContainer = ( void * ) pxList;

	/* 链表节点计数器++ */
	( pxList->uxNumberOfItems )++;
}


/* 将节点按照升序排列插入到链表 */
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem )
{
	ListItem_t *pxIterator;
	
	/* 获取节点的排序辅助值 */
	const uint32_t xValueOfInsertion = pxNewListItem->xItemValue;

	/* 节点要插入到链表的尾部 */
	if( xValueOfInsertion == portMAX_DELAY )
	{
		pxIterator = pxList->xListEnd.pxPrevious;
	}
	else
	{
		for( pxIterator = ( ListItem_t * ) &( pxList->xListEnd );
		     pxIterator->pxNext->xItemValue <= xValueOfInsertion; 
			 pxIterator = pxIterator->pxNext )
		{
			/* 没有事情可做，不断迭代只为了找到节点要插入的位置 */			
		}
	}

	pxNewListItem->pxNext = pxIterator->pxNext;
	pxNewListItem->pxNext->pxPrevious = pxNewListItem;
	pxNewListItem->pxPrevious = pxIterator;
	pxIterator->pxNext = pxNewListItem;

	/* 记住该节点所在的链表 */
	pxNewListItem->pvContainer = ( void * ) pxList;

	/* 链表节点计数器++ */
	( pxList->uxNumberOfItems )++;
}


/* 将节点从链表中删除 */
uint32_t uxListRemove( ListItem_t * const pxItemToRemove )
{
	/* 获取节点所在的链表 */
	List_t * const pxList = ( List_t * ) pxItemToRemove->pvContainer;

	pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
	pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

	/* Make sure the index is left pointing to a valid item. */
	if( pxList->pxIndex == pxItemToRemove )
	{
		pxList->pxIndex = pxItemToRemove->pxPrevious;
	}

	/* 初始化该节点所在的链表为空，表示节点还没有插入任何链表 */
	pxItemToRemove->pvContainer = NULL;
	
	/* 链表节点计数器-- */
	( pxList->uxNumberOfItems )--;

	/* 返回链表中剩余节点的个数 */
	return pxList->uxNumberOfItems;
}