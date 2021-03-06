/**
 * Rapid-prototyping protection schemes with IEC 61850
 *
 * Copyright (c) 2012 Steven Blair
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

package scdCodeGenerator;

import java.util.Iterator;

import org.eclipse.emf.ecore.EObject;

import ch.iec._61850._2006.scl.SclPackage;

public class CFunctionGSELengthCoder extends CFunctionGSECoder {

	public CFunctionGSELengthCoder(EObject obj, CoderType coderType, SCDAdditionalMappings map) {
		super(obj, coderType, map);
		
		this.prefix = "ber_get_length_";
	}
	
	public String getArgs() {
		if (dataType.eClass() == SclPackage.eINSTANCE.getTDataSet()) {
			return "";
		}
		else {
			return "struct " + getName() + " *" + getName();
		}
	}
	
	public String getBody() {
		Iterator<EObject> objects = dataType.eContents().iterator();
		String func = "\tint total = 0;\n\tint len = 0;\n\n";
		
		if (commsType != CommsType.GSE) {
			return null;
		}
		
		while (objects.hasNext()) {
			EObject obj = objects.next();
			
			if (obj == null) {
				return null;
			}

			func = func.concat(getItemCoder(obj, true));
			func = func.concat("\ttotal += len + getLengthBytes(len) + 1;\n");
		}
		
		func = func.concat("\n\treturn total;\n");
		
		return func;
	}
}
