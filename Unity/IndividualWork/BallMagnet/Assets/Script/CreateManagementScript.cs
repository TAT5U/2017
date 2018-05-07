using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CreateManagementScript : MonoBehaviour 
{
	public GameObject[] createObject = new GameObject[2];

	private Vector3 min, max;
	private int count = 0;

	private void Awake()
	{
		StartCoroutine("CreateObject");
	}
	private IEnumerator CreateObject()
	{
		while (true)
		{
			GameObject instatiateObject = Instantiate(createObject[Random.Range(0, 2)]);
			if (count < 1)
			{
				instatiateObject.transform.localPosition = new Vector3(-10, 0, Random.Range(min.z, max.z));
				count++;
			}
			else
			{
				instatiateObject.transform.localPosition = new Vector3(Random.Range(-6, 10), 0, Random.Range(min.z, max.z));
			}
			yield return new WaitForSeconds(2.0f);
		}
	}

	public void MagnetBallNectObjectCall()
	{
		GameObject instatiateObject = Instantiate(createObject[Random.Range(0, 2)]);
		instatiateObject.transform.localPosition = new Vector3(Random.Range(-6, 10), 0, Random.Range(min.z, max.z) + 100);
	}

	public void SetVector(Vector3 minValue, Vector3 maxValue)
	{
		min = minValue;
		max = maxValue;
	}
}
