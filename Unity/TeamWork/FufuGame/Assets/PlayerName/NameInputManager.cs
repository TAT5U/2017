using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class NameInputManager : MonoBehaviour 
{
	private int charaCount_ = 0;
	private const int MAX_CHARA_COUNT = 50;

	[SerializeField]private Vector3 defaultPos;

	[SerializeField]private GameObject japaneseObject;

	[SerializeField]private GameObject[] cursor_ = new GameObject[2];

	private float secondCharaStringPosX;

	private bool isInit = false;

	// Use this for initialization
	void Start () 
	{
		int count = 0;
		Vector3 pos = defaultPos;
		pos.x -= 50.0f;

		while (charaCount_ < MAX_CHARA_COUNT)
		{
			GameObject charaStringObject;
			charaStringObject = Instantiate(japaneseObject);
			charaStringObject.transform.SetParent(transform);
			charaStringObject.GetComponent<RectTransform>().localPosition = pos;
			pos.x += 25.0f;


			if ((charaCount_ + 1) % 5 == 0)
			{
				if ((count + 1) % 5 == 0)
				{
					if (!isInit)
					{
						secondCharaStringPosX = pos.x;

						pos.x += 55.0f;
						pos.y = defaultPos.y;
						isInit = true;
					}
					else
					{
						pos.x = secondCharaStringPosX + 55.0f;
						pos.y -= 25.0f;
					}
				}
				else
				{
					pos.x = defaultPos.x - 50;
					pos.y -= 25.0f;
					count++;
				}
			}
			charaStringObject.name = japaneseObject.name + charaCount_;
			charaCount_++;
		}
		SetCurSor();
	}
	void SetCurSor()
	{
        int count = 0;
        while (count < 2)
        {
            GameObject cursor = Instantiate(cursor_[count]);

            cursor.transform.SetParent(transform);
            cursor.name = "Player" + (count + 1);
           

            if (count == 0)
            {
                cursor.AddComponent<XboxControllerCustom>().mode = PlayerController.E_MODE.PLAYER_1;
            }
            else
            {
                cursor.AddComponent<XboxControllerCustom>().mode = PlayerController.E_MODE.PLAYER_2;

            }

            count++;

        }
    }
}
