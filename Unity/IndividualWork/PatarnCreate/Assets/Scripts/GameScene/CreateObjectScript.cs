using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CreateObjectScript : MonoBehaviour 
{
	private int rad, prev = -99;
	private GameObject instatiateObject;
	private List<GameObject> listObject;
	private GameObject createObject;

	private RandomBoxMuller.RandomBoxMuller rnd;
	void Start()
	{
		listObject = new List<GameObject>();
		createObject = (GameObject)Resources.Load("Prefab/Cube");

		rnd = new RandomBoxMuller.RandomBoxMuller();
	}

	public void CreateObject()
	{

		instatiateObject = Instantiate(createObject);
		rad = Mathf.RoundToInt(Mathf.Abs((float)rnd.next(0, 7) * 10)) % 8;
		while (prev == rad)
		{
			rad = Mathf.RoundToInt(Mathf.Abs((float)rnd.next(0, 7) * 10)) % 8;
		}
		instatiateObject.transform.position = new Vector2(3 * Mathf.Cos((rad * 45) * Mathf.Deg2Rad), 3 * Mathf.Sin((rad * 45) * Mathf.Deg2Rad));
		listObject.Add(instatiateObject);
		prev = rad;
	}

	public void Init()
	{
		prev = -99;
		foreach (var initObject in listObject)
		{
			DestroyObject(initObject);
		}
		listObject = new List<GameObject>();
	}
}
