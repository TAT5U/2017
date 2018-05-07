using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FieldGeneratorScript : MonoBehaviour 
{
	public GameObject instatiateField;

	public void FieldGenerateCall(Vector3 lastFieldPosition)
	{
		GameObject field = Instantiate(instatiateField);
		field.name = gameObject.name;
		field.transform.position = lastFieldPosition;
	}
}
