﻿using UnityEngine;
#if UNITY_EDITOR
using UnityEditor;

namespace UniCAVE
{
    [CustomPropertyDrawer(typeof(MachineName))]
    public class MachineNamePropertyDrawer : PropertyDrawer
    {
        MachineName GetMachineName(SerializedProperty property)
        {
            return fieldInfo.GetValue(property.serializedObject.targetObject) as MachineName;
        }

        public override float GetPropertyHeight(SerializedProperty property, GUIContent label)
        {
            float height = EditorGUIUtility.singleLineHeight;

            if(GetMachineName(property) != null)
            {
                height += EditorGUIUtility.singleLineHeight;
            }

            return height;
        }

        public override void OnGUI(Rect position, SerializedProperty property, GUIContent label)
        {
            Rect machineNameRect = new(position.x, position.y, position.width, EditorGUIUtility.singleLineHeight);

            EditorGUI.PropertyField(machineNameRect, property, label);

            //also show the actual machine name value below
            MachineName machineName = GetMachineName(property);
            if (!machineName) return;
            Rect nameRect = new(position.x, position.y + EditorGUIUtility.singleLineHeight, position.width, EditorGUIUtility.singleLineHeight);

            EditorGUI.indentLevel++;

            GUI.enabled = false;

            EditorGUI.TextField(nameRect, "Name:", machineName.Name);

            GUI.enabled = true;

            EditorGUI.indentLevel--;
        }
    }
}
#endif