using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelectLevelScript : MonoBehaviour
{
	private CreateObjectScript create;
	private IEnumerator coroutine;
	private string level;

	private int enemyOne = 0, enemyTwo = 0, enemyThree = 0, enemyFour = 0, selectRnd = 0, cnt = 0;

	void Start()
	{
		create = gameObject.AddComponent<CreateObjectScript>();

	}

	public void SetLevel(string lv)
	{
		level = lv;
		SelectLevel();
	}

	private void SelectLevel()
	{
		if (level == "LEVEL1")
		{
			create.Init();

			create.CreateObject();
			enemyOne++;
			if (enemyOne < 5)
			{
				Invoke("SelectLevel", 2.0f);
			}
			else
			{
				enemyOne = 0;
			}
		}
		else if (level == "LEVEL2")
		{
			if (enemyOne > 3)
			{
				selectRnd = 2;
				enemyTwo++;
			}
			else if (enemyTwo > 2)
			{
				selectRnd = 1;
				enemyOne++;
			}
			else
			{
				selectRnd = Random.Range(1, 3);
				if (selectRnd == 1)
				{
					enemyOne++;
				}
				else
				{
					enemyTwo++;
				}
			}

			Create();

			if (enemyOne < 4 || enemyTwo < 3)
			{
				Invoke("SelectLevel", 1.40f);
			}
			else
			{
				enemyOne = 0;
				enemyTwo = 0;
			}
		}
		else
		{
			if (enemyTwo > 2)
			{
				if (enemyThree > 1)
				{
					selectRnd = 4;
					enemyFour++;
				}
				else if (enemyFour > 1)
				{
					selectRnd = 3;
					enemyThree++;
				}
				else
				{
					selectRnd = Random.Range(3, 5);
					if (selectRnd == 3)
					{
						enemyThree++;
					}
					else
					{
						enemyFour++;
					}
				}
			}
			else if (enemyThree > 1)
			{
				if (enemyTwo > 2)
				{
					selectRnd = 4;
					enemyFour++;
				}
				else if (enemyFour > 1)
				{
					selectRnd = 2;
					enemyTwo++;
				}
				else
				{
					selectRnd = Random.Range(0, 2);
					if (selectRnd == 0)
					{
						selectRnd = 2;
						enemyTwo++;
					}
					else
					{
						selectRnd = 4;
						enemyFour++;
					}
				}
			}
			else if (enemyFour > 1)
			{
				if (enemyTwo > 2)
				{
					selectRnd = 3;
					enemyThree++;
				}
				else if (enemyThree > 1)
				{
					selectRnd = 2;
					enemyTwo++;
				}
				else
				{
					selectRnd = Random.Range(2, 4);
					if (selectRnd == 2)
					{
						enemyTwo++;
					}
					else
					{
						enemyThree++;
					}
				}
			}
			else
			{
				selectRnd = Random.Range(2, 5);
				if (selectRnd == 2)
				{
					enemyTwo++;
				}
				else if (selectRnd == 3)
				{
					enemyThree++;
				}
				else
				{
					enemyFour++;
				}
			}



			Create();

			if (enemyTwo < 3 || enemyThree < 2 || enemyFour < 2)
			{
				Invoke("SelectLevel", 1.40f);
			}
			else
			{
				enemyTwo = 0;
				enemyThree = 0;
				enemyFour = 0;
			}
		}
	}
	private void Create()
	{
		create.Init();

		while (cnt < selectRnd)
		{
			create.CreateObject();
			cnt++;
		}
		cnt = 0;
		
	}
}
