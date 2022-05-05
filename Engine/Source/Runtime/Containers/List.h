#pragma once

namespace Durna
{
	template<typename ContainerType>
	class LinkedListNode
	{
	public:
		LinkedListNode(ContainerType* InContent)
			: Content(InContent)
		{ };


		LinkedListNode()
			: LinkedListNode(nullptr)
		{ };

		void SetContent(ContainerType* InContent)
		{
			Content = InContent;
		}

		void SetNextNode(LinkedListNode<ContainerType>* InNextNode)
		{
			NextNode = InNextNode;
		}

		LinkedListNode* Next()
		{
			return NextNode;
		}

		ContainerType* operator*()
		{
			return Content;
		}

	private:
		LinkedListNode<ContainerType>* NextNode = nullptr;
		ContainerType* Content;
	};

	template<typename ContainerType>
	class LinkedList
	{
	public:
		LinkedList()
		{ };

		void Add(ContainerType* InElement)
		{
			LinkedListNode<ContainerType>* Node = new LinkedListNode<ContainerType>(InElement);

			Node->SetNextNode(Root);
			Root = Node;
		}

//	private:
		LinkedListNode<ContainerType>* Root = nullptr;
	};

}

