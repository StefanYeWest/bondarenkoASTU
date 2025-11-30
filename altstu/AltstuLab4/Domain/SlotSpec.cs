using System.Collections.Generic;

namespace AltstuLab4.Domain
{
    public sealed class SlotSpec
    {
        public SlotSpec(string pattern, string target, IEnumerable<string>? restrictions = null)
        {
            Pattern = pattern;
            Target = target;
            Restrictions = restrictions is null ? new HashSet<string>() : new HashSet<string>(restrictions);
        }

        public string Pattern { get; }
        public string Target { get; }
        public HashSet<string> Restrictions { get; }
    }
}



